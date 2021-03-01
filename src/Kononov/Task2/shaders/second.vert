#version 330 core

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out VertexData {
    vec3 normal;
    vec2 uv;
} vertex;

void main() {
    gl_Position = vec4(vertex_position, 1);
    vertex.normal = vertex_normal;
    vertex.uv = vertex_uv;
}