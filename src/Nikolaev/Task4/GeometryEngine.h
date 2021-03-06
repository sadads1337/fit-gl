#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector3D>

struct VertexData {
  QVector3D position;
  QVector3D normal;
  QVector2D texture;
  QVector3D tangent;
  QVector3D bitangent;
};

class GeometryEngine {
public:
  GeometryEngine();

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