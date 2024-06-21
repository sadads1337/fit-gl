#version 400
uniform highp mat4 model;
uniform highp mat4 normModel;
uniform highp mat4 projView;

uniform lowp vec3 lightColor;

in highp vec3 position;
in highp vec3 normal;

out lowp vec4 vertexColor;

void main()
{
    vertexColor = vec4(lightColor, 1.0);
    gl_Position = projView * model * vec4(position, 1.f);
}
