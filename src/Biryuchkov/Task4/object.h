#ifndef OBJECT_H
#define OBJECT_H
#include <QOpenGLShaderProgram>
#include <vector>
#include <array>
#include "objectmodel.h"


struct Vertex
{
  std::array<GLfloat , 3> vertex;
  std::array<GLfloat , 3> normal;
  std::array<GLfloat , 2> texCoord;
};

class Object
{
public:
  Object();

  void setObject(const std::vector<GLfloat>& vert ,const std::vector<GLfloat>& norms,const std::vector<GLfloat>& texCoord );

  std::vector<Vertex> vertexs;
};

#endif // OBJECT_H
