#version 130

uniform vec4 col = vec4(1.0, 1.0, 1.0, 1.0);
varying highp vec4 lightingColor;

uniform highp int mask;


void main() {
   if (mask >> 3 == 0) gl_FragColor = col * lightingColor;
   else gl_FragColor = col;
}