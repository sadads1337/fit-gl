#version 120

attribute highp vec3 posAttr;
uniform highp mat4 matrix;
uniform float time;

vec3 param(float time){
    float value = (sin(time) + 1.) / 2.;
    return vec3(value, value, value);
}

void main() {
    //mix(v1, v2, a) = v1 * (1 - a) + v2 * a
    vec3 morphed_vertex = mix(posAttr.xyz, normalize(posAttr.xyz), param(time));
    gl_Position = matrix * vec4(morphed_vertex, 1.);
}
