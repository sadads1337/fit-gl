#version 410 core

layout(triangles, equal_spacing, ccw) in;

in TescData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertices_in[];

out TeseData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertex_out;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main() {
    vertex_out.pos = interpolate3D(vertices_in[0].pos, vertices_in[1].pos, vertices_in[2].pos);
    vertex_out.normal = interpolate3D(vertices_in[0].normal, vertices_in[1].normal, vertices_in[2].normal);
    vertex_out.uv = interpolate2D(vertices_in[0].uv, vertices_in[1].uv, vertices_in[2].uv);
}
