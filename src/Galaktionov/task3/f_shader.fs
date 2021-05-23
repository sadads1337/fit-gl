#version 120

uniform highp int qt_ModeChange;
uniform vec4 qt_color_set;
uniform vec3 viewDir;

uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos = vec3(10.0, 10.0, 0.0);
uniform vec3 viewPos = vec3(0.0, 0.0, 0.0);

varying vec3 v_normal;
varying vec3 v_position;
varying highp vec4 v_lightColor;

void main() {

    //GOURAUD
    if (qt_ModeChange == 0){
        gl_FragColor = v_lightColor * qt_color_set;
    };

    //PHONG
    if (qt_ModeChange == 1){

        // Ambient
        float ambientStrength = 0.1;
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 lightDir = normalize(lightPos - v_position);
        float diffuseAngle = max(dot(v_normal, lightDir), 0.0);
        vec4 diffuse = diffuseAngle * lightColor;

        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - v_position);
        vec3 reflectDir = reflect(-lightDir, v_normal);
        float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 8192);
        vec4 specular = specularStrength * specularAngle * lightColor;

        gl_FragColor = (ambient + diffuse + specular) * qt_color_set;
    };
}
