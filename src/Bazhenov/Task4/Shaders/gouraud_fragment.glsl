#version 120

uniform sampler2D texture;
uniform sampler2D normal_map;

varying vec4 fragment_lighting;
varying vec2 fragment_texture;

void main() {
    vec4 result_texture = texture2D(texture, fragment_texture);
    gl_FragColor = fragment_lighting * result_texture;
}
