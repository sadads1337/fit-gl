#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;
attribute highp vec2 textureAttr;
attribute highp vec3 tangentAttr;

varying highp vec3 fragmentPos;
varying highp vec2 textureCoord;
varying highp mat3 TBN;

uniform highp mat4 model_matrix;
uniform highp mat4 view_matrix;
uniform highp mat4 projection_matrix;

uniform highp vec3 cubeColor;
uniform highp float morph;
uniform highp vec3 lightPos;
uniform highp vec3 viewPos;
uniform highp vec3 lightColor;

void main() {

    // LIGHT
    fragmentPos = vec3(model_matrix * posAttr);

    // MORPHING
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;

    float r = sqrt(x*x + y*y + z*z);
    float theta = acos(z/r);
    float phi = atan(y, x);
    float r_n = normalize(r);

    float morphed_r = morph*r + (1 - morph)*r_n;

    vec3 morphed_norm = morph*normAttr + (1 - morph)*vec3(r_n*sin(theta)*cos(phi), r_n*sin(theta)*sin(phi), r_n*cos(theta));
    vec4 morphed_pos = vec4(morphed_r*sin(theta)*cos(phi), morphed_r*sin(theta)*sin(phi), morphed_r*cos(theta), 1.0);

    gl_Position = projection_matrix * view_matrix * model_matrix * morphed_pos;

    //TEXTURE
    textureCoord = textureAttr;

    vec3 N = normalize(vec3(model_matrix * vec4(morphed_norm, 0.0)));
    vec3 T = normalize(vec3(model_matrix * vec4(tangentAttr, 0.0)));
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);
}
