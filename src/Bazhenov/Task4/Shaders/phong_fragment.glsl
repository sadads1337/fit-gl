#version 120

uniform sampler2D texture;
uniform sampler2D normal_map;

uniform vec3 light_position;
uniform float light_power;

varying vec3 fragment_position;
varying vec3 fragment_normal;
varying vec2 fragment_texture;

varying mat3 TBN;

void main() {
    vec3 normal_from_map = texture2D(normal_map, fragment_texture).rgb;
    normal_from_map = normalize(TBN * (normal_from_map * 2.0F - 1.0F));
    vec3 normal = normal_from_map;

    vec3 light_color = vec3(1.0F, 1.0F, 1.0F);
    vec3 view_position = vec3(0.0F, 0.0F, 0.0F);
    vec3 light_direction = normalize(light_position - fragment_position);

    // Ambient
    float ambient_power = 0.2F;
    vec3 ambient = ambient_power * light_color;

    // Diffuse
    float diffuse_power = max(dot(normal, light_direction), 0.0F);
    vec3 diffuse = diffuse_power * light_color;

    // Specular
    float light_is_outside = max(dot(fragment_normal, light_direction), 0.0F) / dot(fragment_normal, light_direction);
    float specular_power = light_is_outside * 1.0F;
    float specular_exponent = 256.0F;
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float specular_angular = pow(max(dot(view_direction, reflection_direction), 0.0F), specular_exponent);
    vec3 specular = specular_power * specular_angular * light_color;

    vec4 texture_4d = texture2D(texture, fragment_texture);
    vec4 result_texture = vec4(ambient + diffuse + specular, 1.0F) * texture_4d;

    gl_FragColor = result_texture;
}
