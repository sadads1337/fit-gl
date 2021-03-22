#version 330
in vec3 FragPos;
in vec3 Normal;
in vec3 PhongColor;
in vec2 TexCoords;

uniform bool wireframe_enabled;
uniform sampler2D ourTexture;

void main()
{
    if(wireframe_enabled) {
        gl_FragColor = vec4(1, 0.682, 0, 1.0f);
    } else {
        // gl_FragColor = vec4(PhongColor, 1.0f);
        gl_FragColor = vec4(texture(ourTexture, TexCoords).rgb, 1.f) * vec4(PhongColor, 1.0f);
    } 
}
