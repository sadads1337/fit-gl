#pragma once

#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include <QMouseEvent>
#include <QOpenGLTexture>

#include <DirectionInputController.hpp>
#include <MotionInputController.hpp>

#include "Base/GLWindow.hpp"
#include "FirstShader.hpp"

namespace Kononov {

class MainWindow final : public fgl::GLWindow {
  Q_OBJECT
public:
  void init() override;

  void initTextures();

  void render() override;

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

public slots:
  static void onMessageLogged(const QOpenGLDebugMessage& message);

private:
  std::shared_ptr<DirectionInputController> m_look_dir;
  std::shared_ptr<MotionInputController> m_motion;

  std::unique_ptr<QOpenGLBuffer> m_vbo;
  std::unique_ptr<QOpenGLBuffer> m_ibo;
  std::unique_ptr<QOpenGLVertexArrayObject> m_vao;

  std::unique_ptr<QOpenGLDebugLogger> m_logger;

  // Attributes and uniforms handles

  // Shader program handler.
  std::unique_ptr<FirstShader> m_program = nullptr;
  std::unique_ptr<QOpenGLTexture> m_diffuse_map;

  // Frame counter for animation.
  int m_frame = 0;
};

} // namespace Kononov
