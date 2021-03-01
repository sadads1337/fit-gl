#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 4) out;

in VertexData {
    vec3 normal;
    vec2 uv;
} vertices[];

out FragmentData {
    vec3 pos;
    vec3 normal;
    vec2 uv;
} frag;

uniform mat4 model_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;
uniform float skewness;

void handle_vertex(int i) {
    vec3 in_pos = gl_in[i].gl_Position.xyz;

    float angle = in_pos.y * skewness;
    mat3 morph_mat = mat3(cos(angle), 0, -sin(angle), 0, 1, 0, sin(angle), 0, cos(angle));

    vec4 morphed = vec4(morph_mat * in_pos, 1);

    frag.pos = (model_matrix * morphed).xyz;
    frag.normal = normal_matrix * morph_mat * vertices[i].normal;
    frag.uv = vertices[i].uv;

    gl_Position = model_view_matrix * morphed;
    EmitVertex();
}

void main() {
    int i;
    for (i=0; i < 3; i++) {
        handle_vertex(i);
    }
    //handle_vertex(0);

    EndPrimitive();
}
