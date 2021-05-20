#version 130

attribute highp vec3 position;
attribute highp vec3 normal;
uniform highp mat3 normal_matrix;
varying highp vec3 normal_vect;

uniform highp mat4 projection;
uniform highp mat4 view;
uniform highp mat4 model;

uniform highp int mask;

varying highp vec4 lightingColor;
uniform vec3 lightPos;
varying highp vec3 fragPos;

void main() {
    gl_Position = projection * view * model * vec4(position,1.0F);

    normal_vect = normalize(normal_matrix * normal);
    fragPos = vec3(model * vec4(position,1.0F));

    vec4 ambient = vec4(0);
    vec4 diffuse = vec4(0);
    if (mask >> 3 == 0)
    {
        // add ambient color
        vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
        if ( (mask >> 2) % 2 == 1){
            float ambientStrength = 0.1;
            ambient = ambientStrength * lightColor;
        }
        // add diffuse color
        if ( (mask >> 1) % 2 == 1){
            vec3 lightDir = normalize(lightPos - fragPos);
            float diff = max(dot(normal_vect, lightDir), 0.0);
            diffuse = diff * lightColor;
        }
    }
        lightingColor= ambient + diffuse;
}