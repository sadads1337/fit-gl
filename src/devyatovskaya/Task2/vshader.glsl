#version 450

uniform highp mat4 mvp_matrix;
uniform highp float morphFactor;

in highp vec3 posAttr;

const float PI = 3.1415926538;

void main()
{
    highp float newMorphFactor = sin(PI * morphFactor / 2);
    highp vec4 newPos = vec4(
                posAttr * (1 - newMorphFactor) + newMorphFactor * normalize(posAttr),
                1.
    );

    gl_Position = mvp_matrix * newPos;
}
