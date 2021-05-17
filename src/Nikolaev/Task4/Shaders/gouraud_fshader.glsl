#version 110

uniform sampler2D u_texture;
uniform sampler2D u_normMap;

varying vec4 resultLighting;
varying vec2 frag_texture;

void main()
{
    vec4 texture = texture2D(u_texture, frag_texture);
    gl_FragColor = resultLighting * texture;
}