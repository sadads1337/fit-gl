#version 120

uniform vec4 col = vec4(1.0, 0.0, 0.0, 1.0);

uniform vec4 res;
uniform vec3 viewDir;
uniform float spec;
uniform vec3 specular;
uniform int lightModel;

varying vec3 normal;
varying vec3 fragPos; 
varying vec3 lightingColor;

uniform vec3 viewPos = vec3(-2.0, 1.0, 0.0);
uniform vec3 lightPos = vec3(5.0, 0.0, 0.0);

void main() {
    if (lightModel == 1){
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

        // Specular
        float specularStrength = 0.5f;
        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec4 specular = specularStrength * spec * lightColor;

        vec4 res = (ambient + diffuse + specular) * col;
        gl_FragColor = specular + ambient + diffuse;
    };

    if (lightModel == 0){
        // guro
        gl_FragColor = vec4(lightingColor * vec3(col.xyz), 1.0);
    };
}
