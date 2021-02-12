#version 330 core

in vec4 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_uv;

uniform mat4 model_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

void main() {
    gl_Position = model_view_matrix * vertex_position;
    frag_pos = (model_matrix * vertex_position).xyz;
    frag_normal = normal_matrix * vertex_normal;
    frag_uv = vertex_uv;
}