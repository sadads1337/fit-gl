#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;

uniform highp mat4 projection_matrix;
uniform highp mat3 norm_matrix;
uniform highp mat4 model;
uniform highp mat4 view_matrix;
uniform highp float morph_param;
uniform highp vec3 lightPos;
uniform highp vec3 lightColor;
uniform highp vec3 viewPos;
uniform highp int type_of_light_model;

varying highp vec3 v_lightPos;
varying highp vec3 norm_vec;
varying highp vec3 frag_pos;
varying highp vec3 v_viewPos;
varying highp vec3 v_light_color;

float f(float time){
    return (sin(time)+1.0)/2.0;
}

void main() {
    vec3 test_norm_vec = normAttr;
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;
    float rad = sqrt(x*x+y*y+z*z);
    float phi = atan(y,x);
    float theta = acos(z/rad);
    float norm_rad = normalize(rad);
    float morph_rad = morph_param * rad + (1 - morph_param) * norm_rad;
    vec4 morph_posit = vec4(morph_rad * sin(theta) * cos(phi), morph_rad * sin(theta) * sin(phi), morph_rad * cos(theta), 1.0);
    gl_Position = projection_matrix * view_matrix * morph_posit;

    v_viewPos = viewPos;
    v_lightPos = lightPos;

    norm_vec = normalize(norm_matrix * test_norm_vec);
    frag_pos = vec3(model * posAttr);
}