#version 120

uniform mat4 fragment_color_factor;

varying vec4 fragment_color;

void main() {
    gl_FragColor = fragment_color_factor * fragment_color;
}
