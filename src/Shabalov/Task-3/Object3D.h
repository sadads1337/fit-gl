#pragma once

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector2D>
#include <memory>

struct VertexData {
  VertexData(QVector3D p, QVector2D t, QVector3D n)
      : position(p), texCoord(t), normal(n) {}
  QVector3D position;
  QVector2D texCoord;
  QVector3D normal;
};

class Object3D {

public:
  Object3D(const std::vector<VertexData> &vertData, const std::vector<GLuint> &indexes,
           const QImage &texture);
  void init(const std::vector<VertexData> &vertData, const std::vector<GLuint> &indexes,
            const QImage &texture);
  void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
  void rotate(const QQuaternion &r);
  void translate(const QVector3D &t);

private:
  QOpenGLBuffer m_vertexBuffer;
  QOpenGLBuffer m_indexBuffer;
  std::unique_ptr<QOpenGLTexture> m_texture;
  QQuaternion m_rotate;
  QVector3D m_translate;
  float m_scale;
  QMatrix4x4 m_globalTransform;
};
