#version 450
in vec3 FragPos;
in vec3 Normal;
in vec3 PhongColor;
in vec2 TexCoords;

uniform bool wireframe_enabled;
uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
    if (wireframe_enabled) {
        FragColor = vec4(1, 0.682, 0, 1.0f);
    } else {
        FragColor = vec4(PhongColor, 1.0f);
    }
}