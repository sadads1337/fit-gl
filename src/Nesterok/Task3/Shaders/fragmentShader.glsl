#version 130

uniform vec4 col = vec4(1.0, 1.0, 1.0, 1.0);
varying highp vec4 lightingColor;

uniform vec3 lightPos;
varying highp vec3 fragPos;
uniform vec3 viewPos;

varying highp vec3 normal_vect;

uniform highp int mask;


void main() {
   vec4 ambientColor = vec4(0);
   vec4 diffuseColor = vec4(0);
   vec4 specularColor = vec4(0);

   vec3 lightDir = normalize(lightPos - fragPos);
   if (mask >> 3 == 0) gl_FragColor = col * lightingColor;
   else
   {
      // add ambient light
      if ( (mask >> 2) % 2 == 1)
      {
         float ambientStrength = 0.1f;
         ambientColor = ambientStrength * col;
      }
      // add difuse color
      if ( (mask >> 1) % 2 == 1)
      {
      float diffuse_impact = max(dot(normal_vect, lightDir), 0.0);
      diffuseColor =  col * diffuse_impact;
      }
      // add specular color
      if (mask  % 2 == 1)
      {
         float specularStrength = 0.5f;
         vec3 viewDir = normalize(viewPos - fragPos);
         vec3 reflectDir = reflect(-lightDir, normal_vect);
         float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
         specularColor = specularStrength * spec * col;
      }
      gl_FragColor = ambientColor + diffuseColor + specularColor;
   }
}