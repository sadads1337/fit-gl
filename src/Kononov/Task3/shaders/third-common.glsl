#version 330 core

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
