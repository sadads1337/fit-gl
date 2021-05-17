#pragma once

#include <Base/GLWindow.hpp>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QVector3D>
#include <QBasicTimer>
#include <memory>

namespace fgl {

struct VertexData{
  VertexData(){ }
  VertexData(QVector3D p, QVector3D n) :
      position(p), normal(n) { }
  QVector3D position;
  QVector3D normal;
};

class SquareWindow :  public QOpenGLWidget, protected QOpenGLFunctions {

Q_OBJECT

public:
  explicit SquareWindow(QWidget *parent = nullptr);
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void  paintGL() override;
  void change_morph_param(float value);
  void change_type_of_light_model(float value);


private:

  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void timerEvent(QTimerEvent *e) override;
  void init_cube(float width, int N);
  ~SquareWindow() override = default;

  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint normAttr_ = 0;

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  QOpenGLBuffer vertexBuffer;
  QOpenGLBuffer indexBuffer{QOpenGLBuffer::IndexBuffer};

  float morph_param = 1.0;
  float type_of_light_model = 2.0;
  QMatrix4x4 projection_matrix;

  // Frame counter for animation.
  int frame_ = 0;


  QVector2D mousePressPosition{0., 0.};
  QVector3D rotationAxis{0., 0., 1.};
  QBasicTimer timer;
};
} // namespace fgl