#version 120

attribute highp vec4 posAttr;
attribute highp vec3 norm;

uniform highp int lightModel;
uniform highp mat4 matrix;
uniform highp mat4 model;
uniform highp mat3 normal_matrix;
uniform vec3 lightPos = vec3(-5.0, 0.0, 0.0);
uniform vec3 viewPos = vec3(-2.0, 1.0, 0.0);
uniform highp vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

varying vec3 v_normal;
varying vec3 v_fragPos;
varying highp vec4 v_lightColor; // This will be passed into the fragment shader

void main() {
    gl_Position = matrix * posAttr;

    //PHONG
    if (lightModel == 1){
        v_fragPos = vec3(model * posAttr);
        v_normal =  normal_matrix * norm;
    };

    //GOURAUD
    if (lightModel == 0){
        vec3 position = vec3(model * posAttr); // Transform the vertex into eye space
        vec3 normal = normalize(mat3(normal_matrix) * norm); // Transform the normal's orientation into eye space

        // Ambient
        float ambientStrength = 0.1;
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 lightDir = normalize(lightPos - position);  // Get a lighting direction vector from the light to the vertex
        float diffuseAngle = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = diffuseAngle * lightColor;

        // Specular
        float specularStrength = 1.0;
        vec3 viewDir = normalize(viewPos - position);
        vec3 reflectDir = reflect(-lightDir, normal);
        float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 4);
        vec4 specular = specularAngle * specularStrength * vec4(0.0, 0.0, 1.0, 1.0);

        v_lightColor = specular + ambient;
    };
}
