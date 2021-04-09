#version 120

uniform vec4 objectColor = vec4(1.0, 0.0, 0.0, 1.0);


varying vec3 v_lightPos;
varying vec3 v_viewPos;
varying highp vec3 normal_vect;
varying highp vec3 fragment_poss;
varying highp float v_light_model;

varying highp vec4 lightingColor;

void main() {
      if(v_light_model == 1.0){
      float ambient = 0.1;
      vec4 ambientColor = ambient * objectColor;

      vec3 lightDir = normalize(v_lightPos - fragment_poss);
      float diffuse_impact = max(dot(normal_vect, lightDir), 0.0);
      vec4 diffuseColor =  objectColor * diffuse_impact;

      float specularStrength = 0.5f;
      vec3 viewDir = normalize(v_viewPos - fragment_poss);
      vec3 reflectDir = reflect(-lightDir, normal_vect);

      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
      vec4 specularColor = specularStrength * spec * objectColor;

      gl_FragColor = ambientColor + diffuseColor + specularColor;
      }
      else{
        gl_FragColor = objectColor * lightingColor;
      }
}