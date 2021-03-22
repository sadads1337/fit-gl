#version 330
struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform Material material;

struct DirectedLightSource
{
    vec3 direction;
    vec4 color;   
    float intensity;
};
struct PointLightSource
{
    vec3 position;
    vec4 color;   
    float intensity;
};
struct SpotLightSource
{
    vec3 position;
    vec3 direction;
    vec4 color;
    float cutOff;
    float outerCutOff;
    float intensity;
};

uniform DirectedLightSource directed_lights[10];
uniform int directed_lightsCount;
uniform PointLightSource point_lights[10];
uniform int point_lightsCount;
uniform SpotLightSource spot_lights[10];
uniform int spot_lightsCount;


uniform highp mat4 model;
uniform highp mat4 normal_matrix;
uniform highp mat4 view;
uniform highp mat4 projection;
uniform vec3 cameraPos;

in vec3 posAttr;
in vec4 colAttr;
in vec3 normalAttr;
in vec2 textureAttr;
in vec3 tangentAttr;
in vec3 bitangentAttr; 

out vec3 FragPos;
out vec3 Normal;
out vec3 PhongColor;
out vec2 TexCoords;

float attenuation(float dist)
{
   return 1.0f / (1.0f + 0.01f * dist + 0.01f * dist * dist);
}

vec3 process_directed_lights(vec3 norm, vec3 viewDir)
{
    vec3 result = vec3(0);
    for (int i = 0; i < directed_lightsCount; ++i) {
        vec3 lightDir = normalize(directed_lights[i].direction);

        // Составляющая рассеивания
        float diff = max(dot(norm, lightDir), 0.f);
        vec3 diffuse = vec3(directed_lights[i].color) * (diff * vec3(material.diffuse));
        // Составляющая отражения
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular =  vec3(material.specular) * (spec * material.shininess);

        result += (diffuse + specular);
    }
    return result;
}

vec3 process_point_lights(vec3 norm, vec3 viewDir)
{
    vec3 result = vec3(0);
    for (int i = 0; i < point_lightsCount; ++i) {
        vec3 lightDir = normalize(point_lights[i].position - FragPos);
        // Составляющая рассеивания
        float diff = max(dot(norm, lightDir), 0.f);
        vec3 diffuse = vec3(point_lights[i].color) * (diff * vec3(material.diffuse));
        // Составляющая отражения
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = vec3(material.specular) * (spec * material.shininess);

        result += (diffuse + specular) * attenuation(length(FragPos - point_lights[i].position));
    }
    return result;
}


vec3 process_spot_lights(vec3 norm, vec3 viewDir)
{
    vec3 result = vec3(0);
    for (int i = 0; i < spot_lightsCount; ++i) {
        vec3 lightDir = normalize(spot_lights[i].position - FragPos);
        
        // Составляющая рассеивания
        float diff = max(dot(norm, lightDir), 0.f);
        vec3 diffuse = vec3(spot_lights[i].color) * (diff * vec3(material.diffuse));
        // Составляющая отражения
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = vec3(material.specular) * (spec * material.shininess);

        // Расчёты для прожектора
        float theta = dot(lightDir, normalize(-spot_lights[i].direction)); 
        float epsilon = (spot_lights[i].cutOff - spot_lights[i].outerCutOff);
        float intensity = clamp((theta - spot_lights[i].outerCutOff) / epsilon, 0.0, 1.0);
        diffuse  *= intensity;
        specular *= intensity;

        result += (diffuse + specular) * attenuation(length(FragPos - spot_lights[i].position));
    }
    return result;
}

vec3 calculate_lighting()
{
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 norm = normalize(Normal);

    // Фоновая составляющая
    vec3 ambient = vec3(material.ambient);
    vec3 result = ambient;

    result += process_directed_lights(norm, viewDir);
    result += process_point_lights(norm, viewDir);
    result += process_spot_lights(norm, viewDir);

    return result;
}

void main()
{
    FragPos = vec3(model * vec4(posAttr, 1.0));
    Normal = mat3(normal_matrix) * normalAttr;
    TexCoords = textureAttr;

    PhongColor = calculate_lighting();
    gl_Position = projection * view * model * vec4(posAttr, 1.0);
}
