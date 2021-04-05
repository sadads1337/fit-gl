#version 450

in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;

uniform highp mat4 model;
uniform highp mat4 view;
uniform highp mat4 projection;

out vec4 col;

void main()
{
    gl_Position = projection * view * model * vec4(posAttr, 1.0);
    col = colAttr;
}