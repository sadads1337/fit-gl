#version 120

attribute highp vec3 posAttr;
uniform highp mat4 matrix;
uniform float morphFactor;

void main() {
    vec4 newPos = vec4(posAttr * (1 - morphFactor ) + morphFactor * normalize(posAttr), 1.f);
    gl_Position = matrix * newPos;
}