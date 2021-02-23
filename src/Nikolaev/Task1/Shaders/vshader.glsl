#version 110

uniform mat4 mvp_matrix;

attribute vec4 a_position;
attribute vec4 vertex_color;


varying vec4 frag_color;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    frag_color = vertex_color;
}

