#version 330 core

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out vec3 frag_pos;
out vec3 frag_normal;
out vec2 frag_uv;

uniform mat4 model_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

uniform float skewness;

void main() {
    float angle = vertex_position.y * skewness;
    vec4 morphed = vec4(mat3(cos(angle), 0, -sin(angle), 0, 1, 0, sin(angle), 0, cos(angle)) * vertex_position, 1);
    gl_Position = model_view_matrix * morphed;
    frag_pos = (model_matrix * morphed).xyz;
    frag_normal = normal_matrix * vertex_normal;
    frag_uv = vertex_uv;
}