#version 330 core

in VertexData {
    vec3 pos;
    vec2 uv;
    mat3 TBN;
} frag;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;
uniform float ambient_strength;
uniform float specular_strength;
uniform float specular_pow;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

out vec4 frag_color;

vec3 calc_ambient(float ambient_strength, vec3 light_color) {
    return ambient_strength * light_color;
}

vec3 calc_diffuse(vec3 normal, vec3 light_dir, vec3 light_color) {
    vec3 norm = normal;
    float diff = max(dot(norm, light_dir), 0);
    return diff * light_color;
}

vec3 calc_specular(vec3 normal, vec3 light_dir, vec3 view_dir, float specular_strength, float specular_pow, vec3 light_color) {
    vec3 ref_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, ref_dir), 0), specular_pow);
    return specular_strength * spec * light_color;
}


void main() {
    vec3 light_dir = normalize(light_pos - frag.pos);
    vec3 view_dir = normalize(view_pos - frag.pos);

    vec3 local_norm = texture(normal_map, frag.uv).rgb * 2.0 - 1.0;
    vec3 norm = normalize(frag.TBN * local_norm);

    vec3 ambient_light = calc_ambient(ambient_strength, light_color);
    vec3 diffuse_light = calc_diffuse(norm, light_dir, light_color);
    vec3 specular_light = calc_specular(norm, light_dir, view_dir, specular_strength, specular_pow, light_color);

    frag_color = vec4(ambient_light + diffuse_light + specular_light, 1) * texture(diffuse_map, frag.uv);
}