#include "normals.h"

Normals::Normals()
{

}

void Normals::setNormal(const GLfloat _x,const GLfloat _y,const GLfloat _z)
{
    vect = std::vector<GLfloat>{_x,_y,_z};
}
void Normals::setNormal(const std::vector<GLfloat>& vec)
{
    vect = vec;
}

[[nodiscard]] const std::vector<GLfloat>& Normals::getNormal() const noexcept
{
    return vect;
}
