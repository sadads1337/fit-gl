uniform sampler2D qt_Texture0;
//uniform vec4 qt_ColorSet = vec4(1.0, 1.0, 0.0, 1.0);//color

varying highp vec4 qt_TexCoord0;

void main(void)
{
    //qt_ColorSet = vec4(1.0, 1.0, 0.0, 1.0);
    //gl_FragColor = qt_ColorSet;
    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
}
