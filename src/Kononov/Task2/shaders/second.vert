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

uniform float skewness;

void main() {
    float angle = vertex_position.y * skewness;
    vec4 morphed = vec4(mat3(cos(angle), 0, -sin(angle), 0, 1, 0, sin(angle), 0, cos(angle)) * vertex_position, 1);
    gl_Position = model_view_matrix * morphed;
    vertex.pos = (model_matrix * morphed).xyz;
    vertex.normal = normal_matrix * vertex_normal;
    vertex.uv = vertex_uv;
}