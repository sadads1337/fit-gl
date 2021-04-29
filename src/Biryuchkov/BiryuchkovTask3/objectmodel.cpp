#include "objectmodel.h"

void ObjectModel::setTranslate(GLfloat x,GLfloat y,GLfloat z)
{
    tx= x;
    ty= y;
    tz= z;

}
void ObjectModel::setRotate(GLfloat speed,GLfloat x,GLfloat y,GLfloat z)
{
    rspeed = speed ;
    rx=x;
    ry=y;
    rz=z;
}
void ObjectModel::setRotate(GLfloat x,GLfloat y,GLfloat z)
{
    rx=x;
    ry=y;
    rz=z;
}

void ObjectModel::rotate(bool flag)
{
    rotation = flag;
}

QMatrix4x4 ObjectModel::getMatrix()
{
    QMatrix4x4 mat;
    mat.translate(tx,ty,tz);
    if (rotation) frame ++;
    mat.rotate(rspeed*frame , rx,ry,rz);
    return mat;
}

int ObjectModel::frameBack()
{
    return frame;
}

ObjectModel::ObjectModel()
{

}