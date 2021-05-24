#include "normals.h"

Normals::Normals()
{

}

void Normals::setNormal(GLfloat _x,GLfloat _y,GLfloat _z)
{
  vect = std::vector<GLfloat>{_x,_y,_z};
}
void Normals::setNormal(const std::vector<GLfloat>& vec)
{
  vect = vec;
}

const std::vector<GLfloat>& Normals::getNormal()
{
  return vect;
}