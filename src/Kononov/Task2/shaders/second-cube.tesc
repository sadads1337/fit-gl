#version 410 core

layout(vertices = 3) out;

in VertexData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertices_in[];

out TescData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertices_out[];

void main() {
    vertices_out[gl_InvocationID].pos = vertices_in[gl_InvocationID].pos;
    vertices_out[gl_InvocationID].normal = vertices_in[gl_InvocationID].normal;
    vertices_out[gl_InvocationID].uv = vertices_in[gl_InvocationID].uv;
    gl_TessLevelOuter[0] = 5;
    gl_TessLevelOuter[1] = 5;
    gl_TessLevelOuter[2] = 5;
    gl_TessLevelInner[0] = 4;
}
