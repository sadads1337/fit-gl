#version 120

varying lowp vec4 col;
uniform vec4 add_col = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
   gl_FragColor = col;
   gl_FragColor += add_col;
}