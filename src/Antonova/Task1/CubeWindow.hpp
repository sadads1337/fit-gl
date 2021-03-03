#pragma once

#include <Base/GLWindow.hpp>
#include <QMouseEvent>
#include <QColorDialog>

#include <memory> //for unique_ptr

#include <QOpenGLShaderProgram>

namespace fgl {

class CubeWindow final : public GLWindow {
public:
  void init() override;
  void render() override;

  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;


private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colorUniform_ = 0;
  GLint matrixUniform_ = 0;

  unsigned int vertex_buffer = 0;
  unsigned int ibo = 0;

  QVector4D color{1.0, 0.0, 1.0, 0.2};

  QVector2D mousePressPosition;
  QVector3D rotationAxis{0.0, 1.0, 0.0};

  // Shader program handler.
  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;
  //std::unique_ptr is a smart pointer that owns and manages another object 
  //through a pointer and disposes of that object when the unique_ptr goes out of scope

  // Frame counter for animation.
  int frame_ = 0;
};

} // namespace fgl