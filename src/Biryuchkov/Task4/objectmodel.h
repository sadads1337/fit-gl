#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <QOpenGLShaderProgram>


class ObjectModel
{
public:
  ObjectModel();

  void setTranslate(GLfloat x,GLfloat y,GLfloat z);
  void setRotate(GLfloat speed,GLfloat x,GLfloat y,GLfloat z);
  void setRotate(GLfloat x,GLfloat y,GLfloat z);
  void rotate(bool flag);
  QMatrix4x4 getMatrix();
  int frameBack();
private:
  GLfloat rspeed =0;
  GLfloat rx=0;
  GLfloat ry=0;
  GLfloat rz=0;

  GLfloat tx =0 ;
  GLfloat ty =0 ;
  GLfloat tz =0 ;

  int frame=0;

  bool rotation = true;
};

#endif // OBJECTMODEL_H
