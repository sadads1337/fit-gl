#version 120

attribute highp vec4 posAttr;
uniform highp vec4 coord;

void main() {

    gl_Position = matrix * posAttr;
}