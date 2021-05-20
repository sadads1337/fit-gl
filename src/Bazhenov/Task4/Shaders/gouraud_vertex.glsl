#version 120

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform float t;

uniform vec3 light_position;
uniform float light_power;

attribute vec4 vertex_position;
attribute vec3 vertex_normal;
attribute vec2 vertex_texture;
attribute vec3 vertex_tangent;
attribute vec3 vertex_bitangent;

varying vec4 fragment_lighting;
varying vec2 fragment_texture;

void main() {
    // * Morphing * //
    mat4 mv_matrix = view_matrix * model_matrix;
    float factor = (cos(t / 30.0F) + 1.0F) / 2.0F;

    vec3 cube_position_3d = vertex_position.xyz;
    vec3 sphere_position_3d = normalize(cube_position_3d);
    vec3 morphed_position_3d = factor * cube_position_3d + (1.0F - factor) * sphere_position_3d;
    vec3 morphed_normal_3d = factor * vertex_normal + (1.0F - factor) * sphere_position_3d;

    vec4 mv_morphed_position = mv_matrix * vec4(morphed_position_3d, 1.0F);
    gl_Position = projection_matrix * mv_morphed_position;

    // * Gouraud * //
    vec3 mv_position = vec3(mv_morphed_position);
    vec3 mv_normal = normalize(vec3(mv_matrix * vec4(morphed_normal_3d, 0.0F)));

    vec3 light_color = vec3(1.0F, 1.0F, 1.0F);
    vec3 view_position = vec3(0.0F, 0.0F, 0.0F);
    vec3 normal = normalize(mv_normal);
    vec3 light_direction = normalize(light_position - mv_position);

    // Ambient
    float ambient_power = 0.2F;
    vec3 ambient = ambient_power * light_color;

    // Diffuse
    float diffuse_power = max(dot(normal, light_direction), 0.0F);
    vec3 diffuse = diffuse_power * light_color;

    // Specular
    float specular_power = 1.0F;
    float specular_exponent = 16.0F;
    vec3 view_direction = normalize(view_position - mv_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float specular_angular = pow(max(dot(view_direction, reflection_direction), 0.0F), specular_exponent);
    vec3 specular = specular_power * specular_angular * light_color;

    fragment_lighting = vec4(ambient + diffuse + specular, 1.0F);
    fragment_texture = vertex_texture;
}
