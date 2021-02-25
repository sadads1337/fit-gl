#pragma once

#include <Base/GLWindow.hpp>

#include <memory>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QVector3D>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>

namespace fgl {

class SquareWindow final : public GLWindow {
public:
  void init() override;
  void render() override;
  
protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  // Attributes and uniforms handlers.
  GLint posAttr_ = 0;
  GLint colAttr_ = 0;
  GLint matrixUniform_ = 0;

  std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

  // Frame counter for animation.
  int frame_ = 0;

  QOpenGLBuffer indexBuf_{ 
    QOpenGLBuffer::IndexBuffer 
  };
  QOpenGLBuffer arrayBuf_;
  QVector4D square_color {1.0, 1.0, 1.0, 1};
  QVector2D mousePressPosition;
  QVector3D rotationAxis = QVector3D(0.0, 1.0, 0.0).normalized();
};

} // namespace fgl