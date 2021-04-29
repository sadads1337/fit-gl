#include "object.h"



void Object::setObject(const std::vector<GLfloat>& vert ,const std::vector<GLfloat>& norms )
{
    vertex = vert;
    normal = norms;
}

const std::vector<GLfloat>& Object::getVertex()
{
    return vertex;
}
const std::vector<GLfloat>& Object::getNormals()
{
    return normal;
}

std::vector<GLfloat> Object::getData()
{
    int p=0;
    int k=0;
    std::vector<GLfloat> compileVect ={};
    for (int i = 0 ; i < static_cast<int>(vertex.size())/3; ++i)
    {
        for( int l = 0 ; l < 3 ; ++l)
        {
            compileVect.push_back(vertex[p]);
            ++p;
        }
        for( int l = 0 ; l < 3 ; ++l)
        {
            compileVect.push_back(normal[k]);
            ++k;
        }
    }
    return compileVect;
}
