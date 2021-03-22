uniform sampler2D u_texture;
uniform highp vec4 u_color;
varying highp vec4 lightingColor;
void main(void)
{
    vec4 diffMatColor = u_color;
    gl_FragColor = diffMatColor*lightingColor;
}


