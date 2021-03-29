#version 120

attribute highp vec4 posAttr;
uniform highp vec3 norm;
uniform highp mat4 matrix;
uniform highp mat4 matrix2;
uniform highp vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = vec3(-5.0, 0.0, 0.0);
uniform vec3 viewPos = vec3(-2.0, 1.0, 0.0);
varying vec3 LightingColor; 
varying vec3 normal;
varying vec3 fragPos;
void main() {

    //phong
    //gl_Position = matrix * posAttr;
   // fragPos = vec3(matrix2 * posAttr);
   // normal =  norm;

    //guro
    gl_Position = matrix * posAttr;
    // gouraud shading
    vec3 Position = vec3(matrix2 * posAttr);
    vec3 Normal = mat3(matrix2) * norm;
    
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm2 = normalize(Normal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm2, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 1.0; // this is set higher to better show the effect of Gouraud shading 
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;      

    LightingColor = ambient + diffuse + specular;
}