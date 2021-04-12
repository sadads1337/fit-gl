#version 110

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform float t;
uniform float offset_from_face;

uniform vec3 u_lightPosition;
uniform float u_lightPower;

attribute vec4 vertex_position;
attribute vec3 vertex_normal;
attribute vec3 vertex_color;

varying vec3 frag_color;
varying vec3 resultColor;

void main()
{
    /* Morphing and transforming operation */
    mat4 mv_matrix = view_matrix * model_matrix;

    float factor = (sin(t / 30.0) + 1.0) / 2.0;

    vec3 cube_position_3d = vertex_position.xyz + offset_from_face * vertex_normal.xyz;
    vec3 sphere_position_3d = normalize(cube_position_3d);
    vec3 morphed_position_3d = factor * cube_position_3d + (1.0 - factor) * sphere_position_3d;

    gl_Position = projection_matrix * mv_matrix * vec4(morphed_position_3d, 1.0);

    /* Model Gouraud */
    vec3 v_position = vec3(mv_matrix * vec4(morphed_position_3d, 1.0));
    vec3 v_normal = normalize(vec3(mv_matrix * vec4(vertex_normal, 0.0)));

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 viewPos = vec3(0.0, 0.0, 0.0);
    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(u_lightPosition - v_position);

    /* Ambient lighting */
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    /* Diffusive lighting */
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    /* Specular blick lighting */
    float specularStrength = 1.0;
    float specularFactor = 16.0;
    vec3 viewDir = normalize(viewPos - v_position);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularFactor);
    vec3 specular = specularStrength * spec * lightColor;

    resultColor = (ambient  + diffuse + specular) * vertex_color;
    frag_color = vertex_color;
}