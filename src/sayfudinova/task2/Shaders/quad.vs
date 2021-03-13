#version 120

attribute highp vec4 posAttr;
varying highp vec4 posV;

attribute highp vec3 normAttr;
varying highp vec3 normV;

attribute highp vec2 tcAttr;
varying highp vec2 tcV;

uniform highp mat4 modelM;
uniform highp mat4 projM;
uniform highp mat4 viewM;

uniform highp float val;

const float pi = 3.1415926538;

void main() {
    //posAttr.xyz *= 4.0/length(posAttr.xyz);
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;

    float radius = sqrt(x*x + y*y + z*z);
    float phi = atan2(y/x);
    float theta = acos(z/radius);

    vec4 convert = vec4(x*val + (1.0-val)*sin(theta)*cos(phi), y*val + (1.0-val)*sin(theta)*sin(phi), z*val + (1.0-val)*cos(theta), 1.0);

    float nx = normAttr.x;
    float ny = normAttr.y;
    float nz = normAttr.z;

    vec4 normConvert = vec4(nx*val + (1.0-val)*sin(theta)*cos(phi), ny*val + (1.0-val)*sin(theta)*sin(phi), nz*val + (1.0-val)*cos(theta), 1.0);
    gl_Position = projM * modelM * viewM * convert;
    tcV = tcAttr;
    normV = normalize(vec3(modelM * viewM * vec4(normConvert, 0.0)));
    posV = modelM * viewM * convert;
}

