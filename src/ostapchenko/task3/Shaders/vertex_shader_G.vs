#version 120

attribute highp vec4 posAttr;
uniform highp mat4 u_projection_matrix;
uniform highp mat4 u_view_matrix;
uniform highp float u_morph_param;


void main() {

   float x = posAttr.x;
   float y = posAttr.y;
   float z = posAttr.z;
   float r = sqrt(x*x+y*y+z*z);
   float theta = acos(z/r);
   float phi = atan(y, x);

   float r_n = normalize(r);
   float morphed_r = u_morph_param * r + (1 - u_morph_param)*r_n;

   vec4 morphed_poss = vec4(morphed_r*sin(theta)*cos(phi),morphed_r*sin(theta)*sin(phi),morphed_r*cos(theta), 1.0 );

   gl_Position = u_projection_matrix * u_view_matrix * morphed_poss;

}