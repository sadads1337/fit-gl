#version 330 core

in vec3 frag_pos;
in vec3 frag_normal;
in vec2 frag_uv;

uniform sampler2D diffuse_map;
uniform float ambient_strength;
uniform float specular_strength;
uniform float specular_pow;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() {
    vec3 ambient_light = ambient_strength * light_color;

    vec3 norm = normalize(frag_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0);
    vec3 diffuse_light = diff * light_color;

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 ref_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, ref_dir), 0), specular_pow);
    vec3 specular_light = specular_strength * spec * light_color;

    gl_FragColor = vec4(ambient_light + diffuse_light + specular_light, 1) * texture(diffuse_map, frag_uv);
}