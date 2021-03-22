#version 330 core

in vec3 vertex_position;
in vec2 vertex_uv;
in vec3 vertex_normal;

out VertexData {
    vec3 light;
    vec2 uv;
} vertex;

uniform mat4 model_view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Lighting
uniform float ambient_strength;
uniform float specular_strength;
uniform float specular_pow;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

vec3 calc_ambient(float ambient_strength, vec3 light_color);
vec3 calc_diffuse(vec3 normal, vec3 light_dir, vec3 light_color);
vec3 calc_specular(vec3 normal, vec3 light_dir, vec3 view_dir, float specular_strength, float specular_pow, vec3 light_color);

void main() {
    gl_Position = model_view_matrix * vec4(vertex_position, 1);

    vec3 pos = (model_matrix * vec4(vertex_position, 1)).xyz;

    vec3 norm = normalize(normal_matrix * vertex_normal);
    vec3 light_dir = normalize(light_pos - pos);
    vec3 view_dir = normalize(view_pos - pos);

    vec3 ambient_light = calc_ambient(ambient_strength, light_color);
    vec3 diffuse_light = calc_diffuse(norm, light_dir, light_color);
    vec3 specular_light = calc_specular(norm, light_dir, view_dir, specular_strength, specular_pow, light_color);

    vertex.light = ambient_light + diffuse_light + specular_light;
    vertex.uv = vertex_uv;
}