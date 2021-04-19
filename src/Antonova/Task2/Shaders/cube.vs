#version 120

attribute highp vec4 posAttr;

varying lowp vec4 col;

uniform lowp vec4 color;
uniform highp mat4 matrix;
uniform highp float morph;

void main() {
    col = color;

    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;

    float r = sqrt(x*x + y*y + z*z);
    float theta = acos(z/r);
    float phi = atan(y, x);
    float r_n = normalize(r);

    float morphed_r = morph*r + (1 - morph)*r_n;

    vec4 morphed_pos = vec4(morphed_r*sin(theta)*cos(phi), morphed_r*sin(theta)*sin(phi), morphed_r*cos(theta), 1.0 );

    gl_Position = matrix * morphed_pos;
}
