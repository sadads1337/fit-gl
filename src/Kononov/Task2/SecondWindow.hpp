#pragma once

#include <memory>

#include <QMouseEvent>
#include <QOpenGLDebugLogger>

#include <Camera.hpp>
#include <DirectionInputController.hpp>
#include <MotionInputController.hpp>
#include <SceneObject.hpp>

#include "Base/GLWindow.hpp"

namespace Kononov {

class SecondWindow final : public fgl::GLWindow {
  Q_OBJECT
public:
  void init() override;

  void render() override;

protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

public slots:
  static void onMessageLogged(const QOpenGLDebugMessage &message);

private:
  std::unique_ptr<QOpenGLDebugLogger> m_logger;

  std::shared_ptr<DirectionInputController> m_direction_input_controller;
  std::shared_ptr<MotionInputController> m_motion_input_controller;

  std::shared_ptr<Camera> m_camera;

  std::shared_ptr<SceneObject> m_cube;
  std::shared_ptr<SceneObject> m_skull;

  // Frame counter for animation.
  int m_frame = 0;
};

} // namespace Kononov
