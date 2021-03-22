#version 120

attribute highp vec4 posAttr;
uniform highp mat4 matrix;
uniform highp mat4 view_matrix;
uniform highp float morph_param;

float f(float time){
    return (sin(time)+1.0)/2.0;
}

void main() {
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;
    float rad = sqrt(x*x+y*y+z*z);
    float phi = atan(y,x);
    float theta = acos(z/rad);
    float norm_rad = normalize(rad);
    float morph_rad = morph_param * rad + (1 - morph_param) * norm_rad;
    vec4 morph_posit = vec4(morph_rad * sin(theta) * cos(phi), morph_rad * sin(theta) * sin(phi), morph_rad * cos(theta), 1.0);
    gl_Position = matrix * view_matrix * morph_posit;
}