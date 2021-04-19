#version 120


uniform vec3 objectColor = vec3(0.2f, 0.3f, 0.8f);
uniform vec3 lightColor = vec3(1.0f,1.0f,1.0f);

varying vec3 v_lightPos;
varying highp vec3 frag_pos;
varying highp vec3 norm_vec;
varying highp vec3 v_viewPos;
varying highp vec3 v_light_color;
void main() {
    //For PHONG
//   /*
// ambient
    float ambientStrength = 0.2f;
    vec3 ambient = ambientStrength * lightColor;
// diffuse
    vec3 lightDir=normalize(v_lightPos-frag_pos);
    float diffuse_impact = max(dot(norm_vec, lightDir), 0.0);
    vec3 diffuse = diffuse_impact * lightColor;
// specular
    float specularStrength = 0.9f;
    vec3 viewDir = normalize(v_viewPos - frag_pos);
    vec3 reflectDir = reflect(-lightDir, norm_vec);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    vec3 specular = specularStrength * spec * lightColor;

    gl_FragColor = vec4(objectColor*(specular+ambient+diffuse),1.0f);
//  */
    //For GURO
//     gl_FragColor = vec4(objectColor*v_light_color,1.0f);
}