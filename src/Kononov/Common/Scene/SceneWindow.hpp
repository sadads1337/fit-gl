#pragma once

#include <memory>

#include <QOpenGLDebugLogger>

#include <Base/GLWindow.hpp>
#include <SceneObject.hpp>

#include "Camera.hpp"
#include "DirectionInputController.hpp"
#include "MotionInputController.hpp"

namespace Kononov {

constexpr float DEFAULT_FOV = 60.0F;
constexpr float DEFAULT_NEAR_PLANE = 0.1F;
constexpr float DEFAULT_FAR_PLANE = 100.0F;

class SceneWindow : public fgl::GLWindow {
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

  std::shared_ptr<Camera> m_camera;

  std::shared_ptr<DirectionInputController> m_direction_input_controller;
  std::shared_ptr<MotionInputController> m_motion_input_controller;

  std::vector<std::shared_ptr<Controller>> m_controllers;
  std::vector<std::shared_ptr<SceneObject>> m_objects;

  float m_fov = DEFAULT_FOV;
  float m_near = DEFAULT_NEAR_PLANE;
  float m_far = DEFAULT_FAR_PLANE;

public:
  [[nodiscard]] std::shared_ptr<Camera> &getCamera();
  [[nodiscard]] std::shared_ptr<DirectionInputController> &
  getDirectionInputController();
  [[nodiscard]] std::shared_ptr<MotionInputController> &
  getMotionInputController();
  [[nodiscard]] std::vector<std::shared_ptr<Controller>> &getControllers();
  [[nodiscard]] std::vector<std::shared_ptr<SceneObject>> &getObjects();

  [[nodiscard]] float getFov() const;
  void setFov(float fov);
  [[nodiscard]] float getNear() const;
  void setNear(float near);
  [[nodiscard]] float getFar() const;
  void setFar(float far);
};

} // namespace Kononov
