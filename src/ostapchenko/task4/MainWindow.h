#pragma once

#include <Base/GLWindow.hpp>
#include <QBasicTimer>
#include <QMouseEvent>

#include <QOpenGLTexture>
#include <QOpenGLWidget>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
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
class MainWindow : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;
  void initializeGL() override;
  void resizeGL(const int w, const int h) override;
  void paintGL() override;

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void timerEvent(QTimerEvent *e) override;

  // generating cubes
  void initCube(const float width, const int N);

  void initTextures();

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint normAttr_ = 0;
  GLint textureAttr_ = 0;
  GLint tangentAttr_ = 0;
  GLint bitangentAttr_ = 0;

  QMatrix4x4 projection_matrix;

  // buffers
  QOpenGLBuffer vertexBuffer;
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  // animation
  QVector2D mousePressPosition{0., 0.};
  QVector3D rotationAxis{0., 0., 1.};

  QBasicTimer timer;

  std::shared_ptr<QOpenGLTexture> texture = nullptr;
  std::shared_ptr<QOpenGLTexture> normal_map = nullptr;
};

} // namespace fgl