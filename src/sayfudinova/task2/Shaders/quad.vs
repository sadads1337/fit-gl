#version 120

attribute highp vec4 posAttr;
uniform highp mat4 matrix;
uniform float time;

float sinus(float time){
    return (sin(time)+1.0)/2.0;
}

void main() {
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;
    float nx = sqrt(1-y*y/2-z*z/2+y*y*z*z/3);
    float ny = sqrt(1-z*z/2-x*x/2+x*x*z*z/3);
    float nz = sqrt(1-x*x/2-y*y/2+x*x*y*y/3);
    vec4 morph = vec4(x+(x*nx-x)*sinus(time), y+(y*ny-y)*sinus(time), z+(z*nz-z)*sinus(time), 1.0);
    gl_Position = matrix * morph;
}

