attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute highp vec3 a_normal;
attribute highp vec3 a_tangent;
attribute highp vec3 a_bitangent;
uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp mat3 TBN;

void main(void)
{
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;
    vec3 T = normalize(vec3(mv_matrix * vec4(a_tangent, 0.0)));
    vec3 B = normalize(vec3(mv_matrix * vec4(a_bitangent, 0.0)));
    vec3 N = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    TBN = mat3(T, B, N);

    gl_Position = u_projectionMatrix * mv_matrix * a_position;
    v_texcoord = a_texcoord;
    v_position = mv_matrix * a_position;
}
