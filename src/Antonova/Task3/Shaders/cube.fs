#version 120

varying highp vec4 color;
//varying highp vec3 lightColor;
varying highp vec3 normal;
varying highp vec3 fragmentPos;
//varying highp vec3 lightPos_v;
//varying highp vec3 viewPos_v;
//varying highp vec3 cubeColor_v;
//varying highp int light_model_v;

uniform highp vec3 cubeColor;
uniform highp float morph;
uniform highp vec3 lightPos;
uniform highp vec3 viewPos;
uniform highp int lightModel;
uniform highp vec3 lightColor;

void main() {
    if(lightModel == 1)
    {
        // ambient
        float ambientStrength = 0.2f;
        vec3 ambient = ambientStrength * lightColor;

        // diffuse
        vec3 lightDir = normalize(lightPos - fragmentPos);
        float diffuseStrength = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = diffuseStrength * lightColor;

        //specular
        float specularStrength = 0.9f;
        vec3 viewDir = normalize(viewPos - fragmentPos);
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
        vec3 specular = specularStrength * spec * lightColor;

        // result
        vec3 result = (ambient + diffuse + specular) * cubeColor;
        gl_FragColor = vec4(result, 1.0f);
    }
    else
    {
        gl_FragColor = color;
    }
}
