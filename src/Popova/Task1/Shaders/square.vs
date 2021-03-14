#version 120

attribute highp vec4 posAttr;
uniform highp vec4 coord;
uniform highp mat4 matrix;

void main() {

    gl_Position = matrix * posAttr;
}