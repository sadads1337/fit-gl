#version 120


uniform vec3 objectColor = vec3(0.2f, 0.3f, 0.8f);
uniform vec3 lightColor = vec3(1.0f,1.0f,1.0f);

varying vec3 v_lightPos;
varying highp vec3 frag_pos;
varying highp vec3 norm_vec;
varying highp vec3 v_viewPos;
varying highp vec3 v_light_color;
void main() {
    gl_FragColor = vec4(objectColor*v_light_color,1.0f);
}