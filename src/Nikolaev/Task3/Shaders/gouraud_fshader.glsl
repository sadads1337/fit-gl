#version 110

uniform float frag_color_factor;

varying vec3 frag_color;
varying vec3 resultColor;

void main()
{
    if(frag_color_factor > 0.5f)
        gl_FragColor = vec4(frag_color * resultColor, 1.0F);
    else
        gl_FragColor = vec4(frag_color, 1.0f) * 1.0f;
}