#pragma once

#include <QBasicTimer>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <vector>

constexpr int FPS_COUNT = 60;

class GLWidget final : public QOpenGLWidget, protected QOpenGLFunctions {
public:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

  void changeN(int N);
  void changeFactor(int N);

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void timerEvent(QTimerEvent *e) override;
  void initCube(GLfloat halfWidth, std::uint32_t N);

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint matrixUniform_ = 0;
  QVector4D square_color{1.0, 1.0, 1.0, 1.0};

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  QOpenGLShaderProgram program;

  // Create 2 Buffer objects
  QOpenGLBuffer IBO{QOpenGLBuffer::IndexBuffer};
  QOpenGLBuffer VBO{QOpenGLBuffer::VertexBuffer};

  // Variables for rotation
  QVector2D lastPos{0., 0.};
  QVector3D rotationAxis{0., 0., 1.};
  double aspect;
  QBasicTimer FPS_timer; // refresh rate in ms

  std::vector<QVector3D> vertices;
  std::vector<GLushort> indices;
  GLfloat morphFactor;
};
