#include "object.h"

Object::Object()
{

}

void Object::setObject(const std::vector<GLfloat>& vert ,const std::vector<GLfloat>& norms,const std::vector<GLfloat>& texCoord )
{
  vertexs.clear();

  Vertex v;
  for (size_t i = 0 ; i < vert.size()/3 ; i += 1 )
  {
    v.vertex= {vert[i*3],vert[i*3+1],vert[i*3+2]};
    v.normal= {norms[i*3],norms[i*3+1],norms[i*3+2]};
    v.texCoord = {texCoord[i*2],texCoord[i*2+1]};
    vertexs.push_back(v);
  }
}

