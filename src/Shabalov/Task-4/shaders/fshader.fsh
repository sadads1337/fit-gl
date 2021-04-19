uniform sampler2D u_texture;
uniform sampler2D u_normalMap;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
uniform highp vec4 u_color;
varying highp mat3 TBN;

void main(void)
{
    vec3 normal = texture2D(u_normalMap, v_texcoord).rgb;
    normal = normal * 2.0 - 1.0;
    normal = normalize(TBN * normal);

    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 diffMatColor = texture2D(u_texture, v_texcoord);
    vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVect = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 halfVect = normalize(lightVect + eyeVect);
    vec3 reflectLight = normalize(reflect(lightVect, normal));
    float len = length(v_position.xyz - eyePosition.xyz);
    float specularFactor = 16.0;
    float ambientFactor = 0.6;

    vec4 diffColor = diffMatColor * u_lightPower * max(0., dot(normal, -lightVect));
    resultColor += diffColor;
    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor;
    vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0) * u_lightPower * pow(max(0., dot(reflectLight, -halfVect)), specularFactor);
    resultColor += specularColor;
    gl_FragColor = resultColor;
}
