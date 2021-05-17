#version 120

uniform float fragment_color_factor;

uniform vec3 light_position;
uniform float light_power;

varying vec3 fragment_position;
varying vec3 fragment_normal;
varying vec3 fragment_color;

void main() {
    if(fragment_color_factor > 0.5F) {
        vec3 light_color = vec3(1.0F, 1.0F, 1.0F);
        vec3 view_position = vec3(0.0F, 0.0F, 0.0F);
        vec3 normal = normalize(fragment_normal);
        vec3 light_direction = normalize(light_position - fragment_position);

        // Ambient
        float ambient_power = 0.2F;
        vec3 ambient = ambient_power * light_color;

        // Diffuse
        float diffuse_power = max(dot(normal, light_direction), 0.0F);
        vec3 diffuse = diffuse_power * light_color;

        // Specular
        float specular_power = 1.0F;
        float specular_exponent = 256.0F;
        vec3 view_direction = normalize(view_position - fragment_position);
        vec3 reflection_direction = reflect(-light_direction, normal);
        float specular_angular = pow(max(dot(view_direction, reflection_direction), 0.0F), specular_exponent);
        vec3 specular = specular_power * specular_angular * light_color;

        vec3 result_color = (ambient + diffuse + specular) * fragment_color;

        gl_FragColor = vec4(result_color, 1.0F);
    }
    else
        gl_FragColor = vec4(fragment_color, 1.0F);
}
