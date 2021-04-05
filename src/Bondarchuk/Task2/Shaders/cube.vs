#version 120

attribute highp vec4 posAttr;
uniform lowp vec4 colAttr;
uniform lowp vec4 lcolAttr;
uniform highp vec4 coord;
uniform highp mat4 matrix;
uniform float time;

float sinus(float time){
    return (sin(time)+1.0)/2.0;
}

void main() {
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;
    float d1 = sqrt(1-y*y/2-z*z/2+y*y*z*z/3);
    float d2 = sqrt(1-z*z/2-x*x/2+x*x*z*z/3);
    float d3 = sqrt(1-x*x/2-y*y/2+x*x*y*y/3);
    vec4 morphing = vec4(x+(x*d1-x)*sinus(time), y+(y*d2-y)*sinus(time), z+(z*d3-z)*sinus(time), 1.0);
    gl_Position = matrix * morphing;
}