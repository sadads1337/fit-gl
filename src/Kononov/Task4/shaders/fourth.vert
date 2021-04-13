#version 330 core

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;
in vec3 vertex_tangent;
in vec3 vertex_bitangent;

out VertexData {
    vec3 pos;
    vec2 uv;
    mat3 TBN;
} vertex;

uniform mat4 model_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

void main() {
    gl_Position = model_view_matrix * vec4(vertex_position, 1);
    vertex.pos = (model_matrix * vec4(vertex_position, 1)).xyz;
    vertex.uv = vertex_uv;
    vertex.TBN = normal_matrix * mat3(vertex_tangent, vertex_bitangent, vertex_normal);
}