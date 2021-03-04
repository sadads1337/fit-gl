#version 400

uniform highp mat4 mvp_matrix;
uniform highp float morphFactor;

in highp vec3 posAttr;
in lowp vec4 colAttr;
varying lowp vec4 col;

void main()
{
    highp vec4 newPos = vec4( posAttr * (1 - morphFactor ) + morphFactor * normalize(posAttr), 1.);

    col = colAttr;

    gl_Position = mvp_matrix * newPos;
}
