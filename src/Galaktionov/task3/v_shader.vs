#version 120

attribute highp vec4 qt_Vertex;
attribute highp vec3 qt_Normal;

uniform highp int qt_ModeChange;
uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform highp mat3 qt_NormalMatrix;

uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos = vec3(10.0, 10.0, 0.0);
uniform vec3 viewPos = vec3(0.0, 0.0, 0.0);

varying vec3 v_normal;
varying vec3 v_position;
varying highp vec4 v_lightColor;

void main() {
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;

    //PHONG
    if (qt_ModeChange == 1){
        v_position = vec3(qt_ModelViewProjectionMatrix * qt_Vertex);
        v_normal =  normalize(qt_NormalMatrix * qt_Normal);
    };

    //GOURAUD
    if (qt_ModeChange == 0){
        vec3 position = vec3(qt_ModelViewProjectionMatrix * qt_Vertex);
        vec3 normal = normalize(qt_NormalMatrix * qt_Normal);

        // Ambient
        float ambientStrength = 0.1;
        vec4 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 lightDir = normalize(lightPos - position);
        float diffuseAngle = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = diffuseAngle * lightColor;

        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - position);
        vec3 reflectDir = reflect(-lightDir, normal);
        float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 8192);
        vec4 specular = specularStrength * specularAngle * lightColor;

        v_lightColor = ambient/* + diffuse*/ + specular;
    };
}
