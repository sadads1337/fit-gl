#version 110

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform float t;
uniform float offset_from_face;

attribute vec4 vertex_position;
attribute vec3 vertex_normal;
attribute vec2 vertex_texture;
attribute vec3 tangent;
attribute vec3 bitangent;

varying vec3 frag_position;
varying vec3 frag_normal;
varying vec2 frag_texture;
varying mat3 TBN;

void main()
{
    mat4 mv_matrix = view_matrix * model_matrix;

    vec3 T = normalize(vec3(mv_matrix * vec4(tangent, 0)));
    vec3 B = normalize(vec3(mv_matrix * vec4(bitangent, 0)));
    vec3 N = normalize(vec3(mv_matrix * vec4(vertex_normal, 0)));
    TBN = mat3(T, B, N);

    float factor = (sin(t / 30.0) + 1.0) / 2.0;

    vec3 cube_position_3d = vertex_position.xyz + offset_from_face * vertex_normal.xyz;
    vec3 sphere_position_3d = normalize(cube_position_3d);
    vec3 morphed_position_3d = factor * cube_position_3d + (1.0 - factor) * sphere_position_3d;

    gl_Position = projection_matrix * mv_matrix * vec4(morphed_position_3d, 1.0);

    frag_position = vec3(mv_matrix * vec4(morphed_position_3d, 1.0));
    frag_normal = normalize(vec3(mv_matrix * vec4(vertex_normal, 0.0)));
    frag_texture = vertex_texture;
}

