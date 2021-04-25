#version 120

uniform vec4 col = vec4(1.0, 0.0, 0.0, 1.0);
uniform highp int lightModel;
uniform vec3 lightPos = vec3(-5.0, 0.0, 0.0);
uniform vec3 viewPos = vec3(-2.0, 1.0, 0.0);
uniform vec3 viewDir;

varying vec3 v_normal;
varying vec3 v_fragPos;
varying highp vec4 v_lightColor;

void main() {
    //PHONG
    if (lightModel == 1){
        vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);

        // Ambient - фонновая компонента, которая для одной поверхности обычно постоянна, если только не применяется режим color material
        float ambientStrength = 0.1;
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse - рассеянная компонента, которая меняется в зависимости от угла падения лучей света на поверхность по закону косинуса
        vec3 norm = normalize(v_normal);
        vec3 lightDir = normalize(lightPos - v_fragPos);
        float diffuseAngle = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diffuseAngle * lightColor;

        // Specular - бликовая компонента, схожа с рассеянной, но угол между углом падения и углом отражения для specular возводится в степень, равную shininess - блик
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - v_fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec4 specular = specularStrength * specularAngle * lightColor;

        gl_FragColor = (ambient + diffuse + specular) * col;
    };

    //GOURAUD
    if (lightModel == 0){
        gl_FragColor = v_lightColor * col;
    };
}