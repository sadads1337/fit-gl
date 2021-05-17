#version 120

attribute highp vec4 posAttr;
attribute highp vec3 normAttr;

varying highp vec4 color;
varying highp vec3 normal;
varying highp vec3 fragmentPos;

uniform highp mat4 model_matrix;
uniform highp mat4 view_matrix;
uniform highp mat4 projection_matrix;
uniform highp mat3 normal_matrix;

uniform highp vec3 cubeColor;
uniform highp float morph;
uniform highp vec3 lightPos;
uniform highp vec3 viewPos;
uniform highp int lightModel;
uniform highp vec3 lightColor;

void main() {
    // LIGHT
    normal = normalize(normal_matrix * normAttr);
    fragmentPos = vec3(model_matrix * posAttr);

    if(lightModel == 0)
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
        color = vec4(result, 1.0f);
    }

    // MORPHING
    float x = posAttr.x;
    float y = posAttr.y;
    float z = posAttr.z;

    float r = sqrt(x*x + y*y + z*z);
    float theta = acos(z/r);
    float phi = atan(y, x);
    float r_n = normalize(r);

    float morphed_r = morph*r + (1 - morph)*r_n;

    vec4 morphed_pos = vec4(morphed_r*sin(theta)*cos(phi), morphed_r*sin(theta)*sin(phi), morphed_r*cos(theta), 1.0 );

    gl_Position = projection_matrix * view_matrix * model_matrix * morphed_pos;
}
