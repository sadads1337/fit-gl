#pragma once

#include <Base/GLWindow.hpp>

#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include <QVector3D>
#include <chrono>
#include <ctime>
#include <memory>

namespace fgl {

class SquareWindow final : public GLWindow {
public:
  virtual ~SquareWindow() override = default;

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

  QOpenGLBuffer indexBuf_{QOpenGLBuffer::IndexBuffer};
  QOpenGLBuffer arrayBuf_;
  QVector4D square_color{1.0, 1.0, 1.0, 1};
  std::chrono::time_point<std::chrono::system_clock> start;
  QVector2D mousePressPosition{0.0, 0.0};
  QVector3D rotationAxis = QVector3D(0.0, 1.0, 0.0);
};

} // namespace fgl