#version 330
in vec4 col;
in vec2 TexCoords;

uniform sampler2D ourTexture;
uniform bool wireframe_enabled;
out vec4 FragColor;

void main()
{
    if (wireframe_enabled) {
        FragColor = vec4(1, 0.682, 0, 1.0f);
    }
    else {
        FragColor = col;
    }
}
