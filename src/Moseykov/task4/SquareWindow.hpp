#pragma once

#include <Base/GLWindow.hpp>
#include <QBasicTimer>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QVector3D>

namespace fgl {

struct VertexData {
  VertexData(QVector3D p, QVector3D n, QVector2D t, QVector3D tng,
             QVector3D btg)
      : position(p), normal(n), textcoord(t), tangent(tng), bitangent(btg) {}
  QVector3D position;
  QVector3D normal;
  QVector2D textcoord;
  QVector3D tangent;
  QVector3D bitangent;
};
class SquareWindow : public QOpenGLWidget, protected QOpenGLFunctions {

  Q_OBJECT

public:
  explicit SquareWindow(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  ~SquareWindow() override = default;

private:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void timerEvent(QTimerEvent *e) override;
  void init_cube(float width, int N);
  void init_textures();

  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint normAttr_ = 0;
  GLint textureAttr_ = 0;
  GLint tangentAttr_ = 0;
  GLint bitangentAttr_ = 0;

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  QOpenGLBuffer vertexBuffer;
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};

  QMatrix4x4 projection_matrix;

  // Frame counter for animation.
  int frame_ = 0;

  QVector2D mousePressPosition{0., 0.};
  QVector3D rotationAxis{0., 0., 1.};
  QBasicTimer timer;

  std::shared_ptr<QOpenGLTexture> texture = nullptr;
  std::shared_ptr<QOpenGLTexture> normal_map = nullptr;
};

} // namespace fgl