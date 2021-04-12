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

  void drawCubeGeometry(QOpenGLShaderProgram *program,
                        QOpenGLFunctions *functions);
  void initCubeGeometry(float width, unsigned int factor);
  void rotate(const QQuaternion &r);
  void translate(const QVector3D &t);

private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;

  QQuaternion m_rotate;
  QVector3D m_translate;
};

#endif // FIT_GL_GEOMETRYENGINE_H_H
