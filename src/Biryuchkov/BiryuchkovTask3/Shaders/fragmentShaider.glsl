#version 330

out highp vec4 fragColor;

uniform vec4 color;

in vec4 col;

void main()
{
    fragColor = col;
}
