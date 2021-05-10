#version 120

uniform sampler2D texture_for_cube;
uniform sampler2D norm_map;
varying vec3 v_lightPos;
varying highp vec3 frag_pos;
varying highp vec3 v_viewPos;
varying highp vec2 v_text_coord;
varying highp mat3 TBN;
uniform vec3 objectColor = vec3(0.2f, 0.3f, 0.8f);
void main() {
    vec3 norm_vec = texture2D(norm_map, v_text_coord).rgb;
    norm_vec = normalize(TBN*(norm_vec * 2.0 - 1.0));
// ambient
    float ambient = 0.2f;
// diffuse
    vec3 lightDir = normalize(v_lightPos-frag_pos);
    float diffuse = max(dot(norm_vec, lightDir), 0.0);
// specular
    float specularStrength = 0.9f;
    vec3 viewDir = normalize(v_viewPos - frag_pos);
    vec3 reflectDir = reflect(-lightDir, norm_vec);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
    float specular = specularStrength * spec;
    gl_FragColor = (specular+ambient+diffuse) * texture2D(texture_for_cube, v_text_coord);
}