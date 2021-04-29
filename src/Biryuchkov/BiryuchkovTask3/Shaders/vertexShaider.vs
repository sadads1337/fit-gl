#version 330

in vec4 posAttr;
in vec4 norAttr;

uniform mat4 matrix;
uniform mat4 trmatrix;

uniform vec4 directionColor;
uniform vec4 directionPos;
uniform float directionFlag;

uniform vec4 ambientColor;
uniform float ambientFlag;

uniform vec4 pointColor;
uniform vec4 pointPos;
uniform float pointFlag;

uniform vec4 projectorColor;
uniform vec4 projectorPos;
uniform vec4 projectorRot;
uniform float projectorAngle;
uniform float projectorFlag;

uniform float ka;
uniform float kd;
uniform float ks;
uniform int n;
uniform float k;
uniform int p;

out vec4 col;

float cos(vec4 lit , vec4 nor)
{
    float px = lit.x;
    float py = lit.y;
    float pz = lit.z;

    float nx = nor.x;
    float ny = nor.y;
    float nz = nor.z;

    float r = (px*nx+py*ny+pz*nz)/(sqrt(px*px+py*py+pz*pz)*sqrt(nx*nx+ny*ny+nz*nz));

    return max(r,0);
}

float dist(vec4 a ,vec4 b)
{
    float d = 0;

    float px = a.x;
    float py = a.y;
    float pz = a.z;

    float nx = b.x;
    float ny = b.y;
    float nz = b.z;

    return sqrt((px-nx)*(px-nx) + (py-ny)*(py-ny) + (pz-nz)*(pz-nz));
}

float pow(float num , int power)
{
    float res = 1;
    for (int i = 0 ; i < power ; ++i)
    {
        res*=num;
    }
    return res;
}

float cosn(vec4 pos , vec4 norm, vec4 tlr, int n)
{
    float teta = cos(norm , tlr);
    float alf = cos(vec4(0,0,0,1) - pos, norm);

    vec3 cr = cross(norm.xyz, (vec4(0,0,0,1) - pos).xyz );

    float c= 1/(abs(alf-teta) + 1);

    float res = 1;
    for (int i = 0 ; i< n ; i ++)
    {
        res *=c;
    }

    res*= 1/(abs(dot( vec4(cr ,1), tlr)) + 1);

    return res;
}

float angleLimit(vec4 fragPos, vec4 lightPos , vec4 lightRot, float angle)
{
    float teta = cos(fragPos - lightPos , lightRot);
    if ( teta > angle)
        return 1;
    return 0;
}

void main()
{
    vec4 normals = transpose(inverse(trmatrix)) * norAttr;
    vec4 fragPos = trmatrix*posAttr;

    //ambient
    col =ka* ambientColor * ambientFlag;
    //direction
    col += kd* cos(normals,directionPos)*
            directionColor* directionFlag;

    //--------------- Diffuse -----------------//

    vec4 dirFromPoint = normalize(pointPos -fragPos);
    //diffuse point
    col += kd* 1/( 0.0001f *pow(dist(trmatrix*posAttr , pointPos),p) + k)*
            cos(normals,-dirFromPoint)*
            pointColor* pointFlag;
    //specular point
    col += ks* 1/( 0.1f *pow(dist(fragPos , pointPos),p) + k)*
            cosn(fragPos,normals,dirFromPoint,n)*
            pointColor* pointFlag;

    //--------------- Projector ---------------//

    projectorColor;
    projectorPos;
    projectorRot;
    projectorAngle;
    projectorFlag;

    dirFromPoint = normalize(projectorPos -fragPos);
    col += kd* 1/( 0.0001f *pow(dist(fragPos , projectorPos),p) + k)*
            angleLimit(fragPos,projectorPos,projectorRot,projectorAngle)*
            cos(normals,-dirFromPoint)*
            projectorColor* projectorFlag;
    col += ks* 1/( 0.1f *pow(dist(fragPos , projectorPos),p) + k)*
            angleLimit(fragPos,projectorPos,projectorRot,projectorAngle)*
            cosn(fragPos,normals,dirFromPoint,n)*
            projectorColor* projectorFlag;


    gl_Position = matrix * posAttr;
}
