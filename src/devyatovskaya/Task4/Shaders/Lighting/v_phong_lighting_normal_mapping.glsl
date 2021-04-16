#version 450
in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;
in vec2 textureAttr;

in vec3 tangentAttr;
in vec3 bitangentAttr;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
out mat3 TBN;

uniform mat4 model;
uniform mat4 view;
uniform mat4 normal_matrix;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(posAttr, 1.0));
    Normal = mat3(normal_matrix) * normalAttr;
    TexCoords = textureAttr;

    vec3 T = normalize(mat3(normal_matrix) * tangentAttr);
    vec3 B = normalize(mat3(normal_matrix) * bitangentAttr);
    vec3 N = normalize(mat3(normal_matrix) * normalAttr);

    TBN = mat3(T, B, N);

    gl_Position = projection * view * model * vec4(posAttr, 1.0);
}