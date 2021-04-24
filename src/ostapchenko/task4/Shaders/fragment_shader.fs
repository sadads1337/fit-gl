#version 120

uniform vec4 objectColor = vec4(1.0, 0.0, 0.0, 1.0);

varying vec3 v_lightPos;
varying vec3 v_viewPos;
varying highp vec3 fragment_poss;

varying highp vec4 lightingColor;

varying vec2 v_TextCoord;
varying highp mat3 TBN;
uniform sampler2D ourTexture;
uniform sampler2D Normal_map;

void main() {

      vec3 normal = texture2D(Normal_map, v_TextCoord).rgb;
      normal = normalize(TBN*(normal * 2.0 - 1.0));

      float ambient = 0.1;

      vec3 lightDir = normalize(v_lightPos - fragment_poss);
      float diffuse_impact = max(dot(normal, lightDir), 0.0);

      float specularStrength = 0.5f;
      vec3 viewDir = normalize(v_viewPos - fragment_poss);
      vec3 reflectDir = reflect(-lightDir, normal);

      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
      float specular_part = specularStrength * spec;

      gl_FragColor = (ambient + diffuse_impact + specular_part) * texture2D(ourTexture, v_TextCoord);
}