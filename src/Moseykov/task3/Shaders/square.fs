#version 120


uniform vec3 objectColor = vec3(0.2f, 0.3f, 0.8f);
uniform vec3 lightColor = vec3(1.0f,1.0f,1.0f);
uniform vec3 viewPos;
varying vec3 v_lightPos;
varying highp vec3 frag_pos;
varying highp vec3 norm_vec;
varying vec3 v_viewPos;
uniform vec3 lightPos = vec3(3.0,1.0,-1.0);



void main() {
//     float ambientStrength = 0.8f;
//     vec3 ambient = ambientStrength * lightColor;
//     gl_FragColor = vec4(objectColor*ambient,1.0f);
//
//     vec3 lightDir=normalize(lightPos-frag_pos);
//     float diffuse_impact = max(dot(norm_vec, lightDir), 0.0);
//     vec3 diffuse = diffuse_impact * lightColor;
//     gl_FragColor = vec4(objectColor*diffuse,1.0f);
    gl_FragColor = vec4(objectColor,1.0f);




}