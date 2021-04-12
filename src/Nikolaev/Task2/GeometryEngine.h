#ifndef FIT_GL_GEOMETRYENGINE_H_H
#define FIT_GL_GEOMETRYENGINE_H_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>

struct VertexData {
  VertexData(QVector3D p, QVector3D n, QVector3D c)
      : position(p), normal(n), colour(c) {}
  QVector3D position;
  QVector3D normal;
  QVector3D colour;
};

class GeometryEngine : protected QOpenGLFunctions {
public:
  GeometryEngine();
  virtual ~GeometryEngine();

  void drawCubeGeometry(QOpenGLShaderProgram *program);
  void initCubeGeometry(float width, unsigned int factor);

private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
};

#endif // FIT_GL_GEOMETRYENGINE_H_H
