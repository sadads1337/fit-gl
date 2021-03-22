#version 330 core

in VertexData {
    vec3 light;
    vec2 uv;
} frag;

out vec4 frag_color;

uniform sampler2D diffuse_map;

void main() {
    frag_color = vec4(frag.light, 1) * texture(diffuse_map, frag.uv);
}