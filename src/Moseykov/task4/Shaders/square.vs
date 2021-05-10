#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;
attribute highp vec2 textureAttr;
attribute highp vec3 tangentAttr;
attribute highp vec3 bitangentAttr;

uniform highp mat4 projection_matrix;
uniform highp mat3 norm_matrix;
uniform highp mat4 model;
uniform highp mat4 view_matrix;
uniform highp vec3 lightPos;
uniform highp vec3 viewPos;

varying highp vec3 v_lightPos;
varying highp vec3 frag_pos;
varying highp vec3 v_viewPos;
varying highp vec2 v_text_coord;
varying highp mat3 TBN;

void main() {
   mat4 mv_matrix = model * view_matrix;

   v_viewPos = viewPos;
   v_lightPos = lightPos;
   v_text_coord = textureAttr;

   vec3 T = normalize(vec3(mv_matrix * vec4(tangentAttr, 0.0)));
   vec3 B = normalize(vec3(mv_matrix * vec4(bitangentAttr, 0.0)));
   vec3 N = normalize(vec3(mv_matrix * vec4(normAttr, 0.0)));
   TBN = mat3(T, B, N);

   gl_Position = projection_matrix * mv_matrix * posAttr;
   frag_pos = vec3(model * posAttr);
}