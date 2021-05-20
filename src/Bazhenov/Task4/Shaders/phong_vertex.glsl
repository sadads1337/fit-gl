#version 120

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform float t;

attribute vec4 vertex_position;
attribute vec3 vertex_normal;
attribute vec2 vertex_texture;
attribute vec3 vertex_tangent;
attribute vec3 vertex_bitangent;

varying vec3 fragment_position;
varying vec3 fragment_normal;
varying vec2 fragment_texture;

varying mat3 TBN;

void main() {
    mat4 mv_matrix = view_matrix * model_matrix;

    float factor = (cos(t / 30.0F) + 1.0F) / 2.0F;

    vec3 cube_position_3d = vertex_position.xyz;
    vec3 sphere_position_3d = normalize(cube_position_3d);
    vec3 morphed_position_3d = factor * cube_position_3d + (1.0F - factor) * sphere_position_3d;
    vec3 morphed_normal_3d = factor * vertex_normal + (1.0F - factor) * sphere_position_3d;

    vec4 mv_morphed_position = mv_matrix * vec4(morphed_position_3d, 1.0F);
    gl_Position = projection_matrix * mv_morphed_position;

    vec3 T = normalize(vec3(mv_matrix * vec4(vertex_tangent, 0.0F)));
    vec3 B = normalize(vec3(mv_matrix * vec4(vertex_bitangent, 0.0F)));
    vec3 N = normalize(vec3(mv_matrix * vec4(morphed_normal_3d, 0.0F)));
    TBN = mat3(T, B, N);

    fragment_position = vec3(mv_morphed_position);
    fragment_normal = normalize(vec3(mv_matrix * vec4(morphed_normal_3d, 0.0F)));
    fragment_texture = vertex_texture;
}
