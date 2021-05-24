#ifndef SPHERE_H
#define SPHERE_H

#include <QOpenGLShaderProgram>
#include <vector>

class Sphere
{
public:
  Sphere(float stackCount,float sectorCount );

  std::vector<GLfloat> getVertex();
  std::vector<GLfloat> getNormals();
  std::vector<GLfloat> getTexCoord();

private:

  void buildVertex(float stackCount,float sectorCount);
  void buildIndexes(float stackCount,float sectorCount);

  std::vector<GLfloat> vertices;
  std::vector<int> indices;
  std::vector<GLfloat> normals;
  std::vector<GLfloat> texCoords;
};

#endif // SPHERE_H
