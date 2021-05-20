#version 120

attribute highp vec3 position;
attribute highp vec3 normal;

uniform highp mat4 projection;
uniform highp mat4 view;
uniform highp mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(position,1.0F);
}