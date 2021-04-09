#version 330

in vec4 posAttr;
in vec4 norAttr;
in vec2 texCoord;

uniform mat4 matrix;
uniform mat4 trmatrix;

out vec4 normals;
out vec4 fragPos;

out vec2 texCoords;

void main()
{

    texCoords = texCoord;

    normals = normalize(transpose(inverse(trmatrix)) * norAttr);
    fragPos = trmatrix*posAttr;

    gl_Position = matrix * posAttr;
}
