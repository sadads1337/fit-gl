#version 120

uniform float fragment_color_factor;

varying vec3 fragment_color;
varying vec3 result_color;

void main() {
    if(fragment_color_factor > 0.5F)
        gl_FragColor = vec4(result_color, 1.0F);
    else
        gl_FragColor = vec4(fragment_color, 1.0F);
}
