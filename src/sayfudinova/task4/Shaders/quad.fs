#version 120

uniform vec3 lightPos = vec3(-1.0, 2.0, 0.0);
uniform vec3 viewPos = vec3(-1.0, 0.0, 0.0);
uniform sampler2D samplerText;
uniform sampler2D samplerNormMap;

varying highp vec3 v_fragPos;
varying vec2 v_textCoo;
varying highp mat3 TBN;

void main() {
    // выборка вектора из карты нормалей с областью значений [0,1] (.rgb)
    // перевод вектора нормали в интервал [-1,1] (*2.0 - 1.0)
    // перевода из касательного в мировое пространство (TBN)
    vec3 textNormal = normalize(TBN * (texture2D(samplerNormMap, v_textCoo).rgb * 2.0 - 1.0)); // переход от [-1,1] к [0,1]

    // Ambient - фонновая компонента, которая для одной поверхности обычно постоянна, если только не применяется режим color material
    float ambientStrength = 0.1;

    // Diffuse - рассеянная компонента, которая меняется в зависимости от угла падения лучей света на поверхность по закону косинуса
    vec3 lightDir = normalize(lightPos - v_fragPos);
    float diffuseAngle = max(dot(textNormal, lightDir), 0.0);

    // Specular - бликовая компонента, схожа с рассеянной, но угол между углом падения и углом отражения для specular возводится в степень, равную shininess - блик
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - v_fragPos);
    vec3 reflectDir = reflect(-lightDir, textNormal);
    float specularAngle = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    gl_FragColor = (ambientStrength + diffuseAngle + specularStrength * specularAngle) * texture2D(samplerText, v_textCoo);
}