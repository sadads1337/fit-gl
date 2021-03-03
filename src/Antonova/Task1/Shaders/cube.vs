#version 120

attribute highp vec4 posAttr;

varying lowp vec4 col;

uniform lowp vec4 color;
uniform highp mat4 matrix;

void main() {
    col = color;
    gl_Position = matrix * posAttr;
}