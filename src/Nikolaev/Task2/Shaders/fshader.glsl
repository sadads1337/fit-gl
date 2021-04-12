#version 110
uniform float frag_color_factor;

varying vec4 frag_color;

void main()
{
    if(frag_color_factor > 0.5f) gl_FragColor = frag_color;
    else if(frag_color_factor < 0.5f) gl_FragColor = frag_color * 0.0f;
}
