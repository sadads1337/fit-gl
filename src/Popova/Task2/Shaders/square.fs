#version 120

uniform vec4 col = vec4(1.0, 0.0, 0.0, 1.0);
uniform int flag = 0;
void main() {
   if (flag == 1){
      gl_FragColor = col;
   } else
   {
      gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
   }
   
}