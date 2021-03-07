attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute highp vec3 a_normal;
uniform highp mat4 u_projectionMatrix;
uniform highp mat4 u_viewMatrix;
uniform highp mat4 u_modelMatrix;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
uniform highp float u_t;

void main(void)
{
    mat4 mv_matrix = u_viewMatrix * u_modelMatrix;
    float x = a_position.x;
    float y = a_position.y;
    float z = a_position.z;
    float d = sqrt(x*x+y*y+z*z);
    float theta = acos(z/d);
    float phi = atan2(y, x);
    vec4 morphed = vec4(x*u_t + (1.0-u_t)*sin(theta)*cos(phi), y*u_t + (1.0-u_t)*sin(theta)*sin(phi), z*u_t + (1.0-u_t)*cos(theta), 1.0);
    //vec4 morphed = vec4(x*sqrt(1-(y*y/2)-(z*z/2) + (y*y*z*z/3)), y*sqrt(1-(x*x/2)-(z*z/2) + (x*x*z*z/3)), z*sqrt(1-(y*y/2)-(x*x/2) + (y*y*x*x/3)), 1);
    gl_Position = u_projectionMatrix * mv_matrix * morphed;
    v_texcoord = a_texcoord;
    v_normal = normalize(vec3(mv_matrix * vec4(a_normal, 0.0)));
    v_position = mv_matrix * morphed;
}
