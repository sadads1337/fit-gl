attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute highp vec3 a_normal;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower;
uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
varying highp vec4 lightingColor;

void main(void)
{
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;
    gl_Position = u_projectionMatrix * mv_matrix * a_position;
    v_texcoord = a_texcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    v_position = mv_matrix * a_position;

    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 lightColor = vec4(1.0, 1.0, 1.0, 0.0);
    vec4 u_lightPosition = vec4(0.0, 0.0, 0.0, 1.0);
    vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);
    vec3 lightVect = normalize(v_position.xyz - u_lightPosition.xyz);
    vec3 reflectLight = normalize(reflect(lightVect, v_normal));
    float specularFactor = 50.0;
    float ambientFactor = 0.1;
    float u_lightPower = 1.0f;

    vec4 diffColor = lightColor * u_lightPower * max(0., dot(v_normal, -lightVect));
    resultColor += diffColor;
    vec4 ambientColor = ambientFactor * lightColor;
    resultColor += ambientColor;
    vec4 specularColor = lightColor * u_lightPower * pow(max(0., dot(reflectLight, -eyeVect)), specularFactor);
    resultColor += specularColor;
    lightingColor = resultColor;
}
