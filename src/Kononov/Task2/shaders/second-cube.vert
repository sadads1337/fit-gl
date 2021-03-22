#version 410 core

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out VertexData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertex;

void main() {
    vertex.pos = vertex_position;
    vertex.normal = vertex_normal;
    vertex.uv = vertex_uv;
}