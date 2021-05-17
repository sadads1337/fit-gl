#version 110
uniform sampler2D u_texture;
uniform sampler2D u_normMap;
uniform float frag_color_factor;
uniform vec3 u_lightPosition;
uniform float u_lightPower;

varying vec3 frag_position;
varying vec3 frag_normal;
varying vec2 frag_texture;
varying mat3 TBN;

void main()
{
    //    vec3 norm = normalize(frag_normal);
    vec3 norm = texture2D(u_normMap, frag_texture).rgb;
    norm = norm * 2.0 - 1.0;
    norm = normalize(TBN * norm);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 viewPos = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = normalize(u_lightPosition - frag_position);

    /* Ambient lighting */
    float ambientStrength = 0.95;
    vec3 ambient = ambientStrength * lightColor;

    /* Diffusive lighting */
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    /* Specular blick lighting */
    float specularStrength = 1.0;
    float specularFactor = 256.0;
    vec3 viewDir = normalize(viewPos - frag_position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularFactor);
    vec3 specular = specularStrength * spec * lightColor;

    vec4 texture4 = texture2D(u_texture, frag_texture);
    vec4 resultTexture = vec4(ambient  + diffuse + specular, 1.0) * texture4;

    gl_FragColor = resultTexture;
}
