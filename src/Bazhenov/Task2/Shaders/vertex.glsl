#version 120

uniform mat4 mvp_matrix;

attribute vec4 vertex_position;
attribute vec4 vertex_color;

varying vec4 fragment_color;

void main() {
    gl_Position = mvp_matrix * vertex_position;

    fragment_color = vertex_color;
}
