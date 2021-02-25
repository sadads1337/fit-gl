#version 330

layout(triangles) in;
layout(line_strip, max_vertices = 4) out;

in VertexData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} vertices[];

out FragmentData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} frag;

void main() {
    int i;
    for (i=0; i < 3; i++) {
        frag.pos = vertices[i].pos;
        frag.normal = vertices[i].normal;
        frag.uv = vertices[i].uv;

        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    frag.pos = vertices[0].pos;
    frag.normal = vertices[0].normal;
    frag.uv = vertices[0].uv;

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
}
