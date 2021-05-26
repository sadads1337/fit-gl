#version 120

uniform highp int modeChange;
uniform vec4 col;
uniform vec3 viewDir;

uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos = vec3(0.3, 0.0, 2.5);
uniform vec3 viewPos = vec3(0.0, 0.0, 0.0);
uniform float ambientStrength = 0.1;

varying vec3 v_normal;
varying vec3 v_position;
varying highp vec4 v_lightColor;


void main() {

    //GOURAUD
    if (modeChange == 0){
        gl_FragColor = v_lightColor * col;
    };

    //PHONG
    if (modeChange == 1){

        // Ambient
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 lightDir = normalize(lightPos - v_position);
        float diffuseAngle = max(dot(v_normal, lightDir), 0.0);
        vec4 diffuse = diffuseAngle * lightColor;

        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - v_position);
        vec3 reflectDir = reflect(-lightDir, v_normal);
        float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 1000);
        vec4 specular = specularStrength * specularAngle * lightColor;

        gl_FragColor = (ambient + diffuse + specular) * col;
    };
}
