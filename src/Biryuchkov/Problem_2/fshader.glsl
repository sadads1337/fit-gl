#version 400
uniform lowp vec4 global_color;

void main()
{
    gl_FragColor = global_color;
}
