#version 120

attribute highp vec4 v_pos;
attribute highp vec3 normal;

uniform highp int modeChange;
uniform highp mat4 MVPMatrix;
uniform highp mat3 normalMatrix;

uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos = vec3(0.3, 0.0, 2.5);
uniform vec3 viewPos = vec3(0.0, 0.0, 0.0);
uniform float ambientStrength = 0.1;

varying vec3 v_normal;
varying vec3 v_position;
varying highp vec4 v_lightColor;

void main() {
    gl_Position = MVPMatrix * v_pos;

    //PHONG
    if (modeChange == 1){
        v_position = vec3(MVPMatrix * v_pos);
        v_normal =  normalize(normalMatrix * normal);
    };

    //GOURAUD
    if (modeChange == 0){
        vec3 position = vec3(MVPMatrix * v_pos);
        vec3 normal = normalize(normalMatrix * normal);

        // Ambient
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 lightDir = normalize(lightPos - position);
        float diffuseAngle = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = diffuseAngle * lightColor;

        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - position);
        vec3 reflectDir = reflect(-lightDir, normal);
        float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 8);
        vec4 specular = specularStrength * specularAngle * lightColor;

        v_lightColor = ambient + diffuse + specular;
    };
}
