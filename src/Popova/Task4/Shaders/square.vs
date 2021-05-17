#version 120

attribute highp vec4 posAttr;
attribute highp vec3 norm;
attribute highp vec2 textCoord;
uniform highp mat4 matrix;
uniform highp int lightModel;
uniform highp mat4 model;
uniform highp mat3 normal_matrix;
uniform highp vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = vec3(-5.0, 0.0, 0.0);
uniform vec3 viewPos = vec3(-2.0, 1.0, 0.0);
varying vec3 LightingColor; 
varying vec3 normal;
varying float light_model;
varying vec3 fragPos;
attribute vec2 a_texcoord;
attribute vec3 tangent;
attribute vec3 bitangent;
varying vec2 v_texcoord;
varying mat3 TBN;
void main() {
    v_texcoord = a_texcoord;
    light_model = lightModel;
    gl_Position = matrix * posAttr;
    vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(model * vec4(norm, 0.0)));
    TBN = mat3(T, B, N);
    if (lightModel == 1){
        //phong
        fragPos = vec3(model * posAttr);
        normal =  normal_matrix * norm;
    };

    if (lightModel == 0){
        //guro
        // gouraud shading
        vec3 Position = vec3(model * posAttr);
        vec3 Normal = mat3(normal_matrix) * norm;
        
        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
        
        // diffuse 
        vec3 norm2 = normalize(Normal);
        vec3 lightDir = normalize(lightPos - Position);
        float diff = max(dot(norm2, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        
        // specular
        float specularStrength = 0.5f; 
        vec3 viewDir = normalize(viewPos - Position);
        vec3 reflectDir = reflect(-lightDir, norm2); 
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec3 specular = spec * specularStrength * lightColor;      

        LightingColor = specular + ambient + diffuse;
       
    };

}