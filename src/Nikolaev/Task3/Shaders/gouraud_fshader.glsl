#version 110

uniform float frag_color_factor;

varying vec3 frag_color;
varying vec3 resultColor;

void main()
{
    if(frag_color_factor > 0.5)
        gl_FragColor = vec4(resultColor, 1.0);
    else
        gl_FragColor = vec4(frag_color, 1.0) * 1.0;
}