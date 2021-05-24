#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;
attribute highp vec2 textureAttr;
attribute highp vec3 tangentAttr;

uniform highp mat4 matrix;
uniform highp mat4 model;
uniform highp mat3 normal_matrix;

varying highp vec3 v_fragPos;
varying highp vec2 v_textCoo;
varying highp mat3 TBN;

void main() {
    gl_Position = matrix * posAttr;
    v_fragPos = vec3(model * posAttr);

    v_textCoo = textureAttr;
    vec3 T = normalize(vec3(matrix * vec4(tangentAttr, 0.0)));
    vec3 N = normalize(vec3(matrix * vec4(normAttr, 0.0)));
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);
}
