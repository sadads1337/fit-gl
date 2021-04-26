#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;
attribute highp vec2 textureAttr;
attribute highp vec3 tangentAttr;
attribute highp vec3 bitangentAttr;

uniform highp mat4 u_projection_matrix;
uniform highp mat4 u_view_matrix;
uniform highp mat4 u_model_matrix;
uniform highp mat3 normal_matrix;
uniform vec3 lightPos;
uniform vec3 viewPos;

varying highp vec3 fragment_poss;
varying vec3 v_lightPos;
varying vec3 v_viewPos;

varying vec2 v_TextCoord;
varying highp mat3 TBN;


void main() {

   mat4 mv_matrix = u_model_matrix * u_view_matrix;

   v_TextCoord = textureAttr;
   vec3 T = normalize(vec3(mv_matrix * vec4(tangentAttr, 0.0)));
   vec3 B = normalize(vec3(mv_matrix * vec4(bitangentAttr, 0.0)));
   vec3 N = normalize(vec3(mv_matrix * vec4(normAttr, 0.0)));
   TBN = mat3(T, B, N);

   v_lightPos = lightPos;
   v_viewPos = viewPos;

   gl_Position = u_projection_matrix * mv_matrix * posAttr;
   fragment_poss = vec3(u_model_matrix * posAttr);

}