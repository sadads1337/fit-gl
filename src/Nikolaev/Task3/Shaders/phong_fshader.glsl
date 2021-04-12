#version 110
uniform float frag_color_factor;
uniform vec3 u_lightPosition;
uniform float u_lightPower;

varying vec3 frag_position;
varying vec3 frag_normal;
varying vec3 frag_color;

void main()
{
    if(frag_color_factor > 0.5f) {
        vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
        vec3 viewPos = vec3(0.0, 0.0, 0.0);
        vec3 norm = normalize(frag_normal);
        vec3 lightDir = normalize(u_lightPosition - frag_position);

        /* Ambient lighting */
        float ambientStrength = 0.1f;
        vec3 ambient = ambientStrength * lightColor;

        /* Diffusive lighting */
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        /* Specular blick lighting */
        float specularStrength = 1.0f;
        float specularFactor = 256.0f;
        vec3 viewDir = normalize(viewPos - frag_position);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularFactor);
        vec3 specular = specularStrength * spec * lightColor;

        vec3 resultColor = (ambient  + diffuse + specular) * frag_color;

        gl_FragColor = vec4(resultColor, 1.0f);
    }
    else if(frag_color_factor < 0.5f) gl_FragColor = vec4(frag_color, 1.0f) * 1.0f;
}
