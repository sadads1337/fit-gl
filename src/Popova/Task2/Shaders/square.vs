#version 120

attribute highp vec4 posAttr;
uniform highp vec4 coord;
uniform highp mat4 matrix;
uniform float time;

float f(float time){
    return (sin(time)+1.0)/2.0;
    //return 0.0;
}
void main() {
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;
    float d = sqrt(1-y*y/2-z*z/2+y*y*z*z/3);
    float d2 = sqrt(1-z*z/2-x*x/2+x*x*z*z/3);
    float d3 = sqrt(1-x*x/2-y*y/2+x*x*y*y/3);
    vec4 morphing = vec4(x+(x*d-x)*f(time), y+(y*d2-y)*f(time), z+(z*d3-z)*f(time), 1.0);
    //r1 = normalize(r);
    //r2 = t*r+(1-t)*r1;
    gl_Position = matrix * morphing;
}