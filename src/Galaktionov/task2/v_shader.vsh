attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_MultiTexCoord0;

uniform highp mat4 qt_ModelViewProjectionMatrix;
uniform float time;

varying highp vec4 qt_TexCoord0;

float sinus(float time) {
    return (sin(time)+1.0)/2.0;
}

void main(void)
{
    float x = qt_Vertex.x;
    float y = qt_Vertex.y;
    float z = qt_Vertex.z;
    float d1 = sqrt(1 - y * y / 2 - z * z / 2 + y * y * z * z / 3);
    float d2 = sqrt(1 - z * z / 2 - x * x / 2 + x * x * z * z / 3);
    float d3 = sqrt(1 - x * x / 2 - y * y / 2 + x * x * y * y / 3);
    vec4 morphing = vec4(x + (x * d1 - x) * sinus(time), y + (y * d2 - y) * sinus(time), z + (z * d3 - z) * sinus(time), 1.0);
    gl_Position = qt_ModelViewProjectionMatrix * morphing;
    qt_TexCoord0 = qt_MultiTexCoord0;
}
