#version 330

out highp vec4 fragColor;

uniform vec4 color;

uniform mat4 trmatrix;

uniform vec4 directionColor;
uniform vec4 directionPos;
uniform float directionFlag;

uniform vec4 ambientColor;
uniform float ambientFlag;

uniform vec4 pointColor;
uniform vec4 pointPos;
uniform float pointFlag;

uniform float ka;
uniform float kd;
uniform float k;
uniform int p;

uniform sampler2D textureMap;
uniform sampler2D normalMap;

in vec4 normals;
in vec4 fragPos;

in vec2 texCoords;

vec3 calcNormalFromNormalmap(vec3 localNormal,vec2 uv)
{
    vec3 n = normalize(localNormal.xyz);
    vec3 t = normalize(cross(n,vec3(1,1,1)));
    vec3 b = cross(n,t);

    vec3 normal = texture(normalMap , uv).rgb;
    normal = normalize(normal*2.0f - 1.0f);

    vec3 resultingNormal = normalize(normal.x*t+normal.y*b+normal.z*n);
    return resultingNormal;
}

void main()
{
    vec4 actualNormal  = vec4(calcNormalFromNormalmap(normals.xyz, texCoords),1);

    //ambient
    vec4 col =ka* ambientColor * ambientFlag;
    //direction
    col += 0.01*kd* max(dot(actualNormal,directionPos),0)*
            directionColor* directionFlag;

    //--------------- Point -----------------//
    vec4 lightDir = normalize(pointPos -fragPos);

    //diffuse point
    col += kd* 1/( 0.0002f *pow(distance(fragPos , pointPos),p) + k)*
            max(dot(actualNormal,lightDir),0)*
            pointColor* pointFlag;

    //texture2D(texture, texCoords);
    fragColor =  texture(textureMap, texCoords) * col;
}
