#version 120

uniform sampler2D tcU;

uniform highp vec4 lightPosU;
uniform highp float lightPowU;
uniform highp vec4 colU;

varying highp vec4 posV;
varying highp vec3 normV;
varying highp vec2 tcV;

void main() {
    vec4 resultCol = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 eyePos = vec4(0.0, 0.0, 0.0, 1.0);

    vec3 eyeV = normalize(posV.xyz - eyePos.xyz);
    vec3 lightV = normalize(posV.xyz - lightPosU.xyz);
    vec3 lightRef = normalize(reflect(lightV, normV);

    float len = length(posV.xyz - eyePos.xyz);
    float specularFactor = 50.0;
    float ambientFactor = 0.1;

    vec4 diffCol = colU * lightPowU * max(0, dot(normV, -lightV));
    resultCol += diffCol;

    vec4 ambientCol = ambientFactor * colU;
    resultCol += ambientCol;

    vec4 specularCol = vec4(1.0, 1.0, 1.0, 1.0) * lightPowU * pow(max(0, dot(lightRef, -lightV)), specularFactor);
    resultCol += specularCol;

    gl_FragColor = resultCol;
}