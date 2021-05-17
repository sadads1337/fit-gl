#version 120

varying highp vec3 fragmentPos;
varying highp vec2 textureCoord;
varying highp mat3 TBN;

uniform highp vec3 cubeColor;
uniform highp float morph;
uniform highp vec3 lightPos;
uniform highp vec3 viewPos;
uniform highp int lightModel;
uniform highp vec3 lightColor;
uniform sampler2D texture;
uniform sampler2D normalMap;


void main() {

        // normal mapping
        vec3 normal = texture2D(normalMap, textureCoord).rgb;
        normal = normalize(TBN * (normal * 2.0 - 1.0));

        // ambient
        float ambientStrength = 0.3f;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 lightDir = normalize(lightPos - fragmentPos);
        float diffuseStrength = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diffuseStrength * lightColor;

        //specular
        float specularStrength = 0.9f;
        vec3 viewDir = normalize(viewPos - fragmentPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
        vec3 specular = specularStrength * spec * lightColor;

        // result
        vec3 result = (ambient + diffuse + specular) * cubeColor;
        gl_FragColor = vec4(result, 1.0f) * texture2D(texture, textureCoord);
        //gl_FragColor = (ambientStrength + diffuseStrength + specularStrength * spec) * texture2D(texture, textureCoord);

}
