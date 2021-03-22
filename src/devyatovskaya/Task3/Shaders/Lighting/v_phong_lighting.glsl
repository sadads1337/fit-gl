#version 330

in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;
in vec2 textureAttr;
in vec3 tangentAttr;
in vec3 bitangentAttr; 

out vec3 FragPos;
out vec3 Normal;
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

    vec3 T = normalize(vec3(model * vec4(tangentAttr,   0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangentAttr, 0.0)));
    vec3 N = normalize(vec3(model * vec4(normalAttr,    0.0)));
    mat3 TBN = mat3(T, B, N);

    gl_Position = projection * view * model * vec4(posAttr, 1.0);
}
