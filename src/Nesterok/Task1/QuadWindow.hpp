#pragma once

#include "Base/GLWindow.hpp"
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class MainWindow final : public fgl::GLWindow{
public:
  void init() override;
  void render() override;

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colAttr_ = 0;
  GLint matrixUniform_ = 0;
  QVector4D additional_color{0.0, 0.0, 0.0, 1.0};

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
};
