#version 120

uniform vec4 col = vec4(1.0, 0.0, 0.0, 1.0);
varying vec3 normal;
varying vec3 fragPos; 
varying vec3 LightingColor; 
uniform vec3 lightPos = vec3(-5.0, 0.0, 0.0);
uniform vec4 result;
uniform vec3 viewDir;
uniform float spec;
uniform vec3 specular;
varying float light_model;

uniform vec3 viewPos = vec3(-2.0, 1.0, 0.0);
void main() {
    if (light_model == 1){
        //phong
        // Ambient
        vec4 lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
        float ambientStrength = 0.1f;
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse 
        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(lightPos - fragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * lightColor;

        //specular
        float specularStrength = 0.5f;
        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec4 specular = specularStrength * spec * lightColor;

        vec4 result = (ambient + diffuse + specular) * col;
        gl_FragColor = result;
    };

    if (light_model == 0){
        // guro
        gl_FragColor = vec4(LightingColor * vec3(col.xyz), 1.0);
    };
}