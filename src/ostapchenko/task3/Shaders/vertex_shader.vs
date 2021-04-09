#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;

uniform highp mat4 u_projection_matrix;
uniform highp mat4 u_view_matrix;
uniform highp mat4 u_model_matrix;
uniform highp float u_morph_param;
uniform highp mat3 normal_matrix;
uniform highp int light_model;
uniform vec3 lightPos;
uniform vec3 viewPos;

varying highp float v_light_model;
varying highp vec3 normal_vect;
varying highp vec3 fragment_poss;
varying vec3 v_lightPos;
varying vec3 v_viewPos;

varying highp vec4 lightingColor;


void main() {

   v_light_model = light_model;
   v_lightPos = lightPos;
   v_viewPos = viewPos;
   mat4 mv_matrix = u_model_matrix * u_view_matrix;

   float x = posAttr.x;
   float y = posAttr.y;
   float z = posAttr.z;
   float r = sqrt(x*x+y*y+z*z);
   float theta = acos(z/r);
   float phi = atan(y, x);

   float r_n = normalize(r);
   float morphed_r = u_morph_param * r + (1 - u_morph_param)*r_n;

   vec4 morphed_poss = vec4(morphed_r*sin(theta)*cos(phi),morphed_r*sin(theta)*sin(phi),morphed_r*cos(theta), 1.0 );

   gl_Position = u_projection_matrix * mv_matrix * morphed_poss;

   normal_vect = normalize(normal_matrix * normAttr);
   fragment_poss = vec3(u_model_matrix * posAttr);

   if(light_model == 0){
       vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
       float ambientStrength = 0.1;
       vec4 ambient = ambientStrength * lightColor;

       vec3 lightDir = normalize(lightPos - fragment_poss);
       float diff = max(dot(normal_vect, lightDir), 0.0);
       vec4 diffuse = diff * lightColor;

       float specularStrength = 0.5f;
       vec3 viewDir = normalize(viewPos - fragment_poss);
       vec3 reflectDir = reflect(-lightDir, normal_vect);
       float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
       vec4 specular = spec * specularStrength * lightColor;

       lightingColor = specular + ambient + diffuse;
   }

}