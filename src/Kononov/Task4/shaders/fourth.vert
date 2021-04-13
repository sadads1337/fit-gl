#version 330 core

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out VertexData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertex;

uniform mat4 model_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

void main() {
    gl_Position = model_view_matrix * vec4(vertex_position, 1);
    vertex.pos = (model_matrix * vec4(vertex_position, 1)).xyz;
    vertex.normal = normal_matrix * vertex_normal;
    vertex.uv = vertex_uv;
}