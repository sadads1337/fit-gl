#pragma once

#include <memory>
#include <vector>

#include <QMouseEvent>
#include <QOpenGLDebugLogger>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include <Camera.hpp>
#include <ConstantRotationController.hpp>
#include <DirectionInputController.hpp>
#include <MotionInputController.hpp>
#include <SceneObject.hpp>

#include <FirstShader.hpp>

#include "Base/GLWindow.hpp"

namespace Kononov {

class ThirdWindow final : public fgl::GLWindow {
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
  void add_objects(QVector3D translation,
                   const std::shared_ptr<QOpenGLShaderProgram> &program);

  std::unique_ptr<QOpenGLDebugLogger> m_logger;

  std::shared_ptr<Camera> m_camera;

  std::shared_ptr<DirectionInputController> m_direction_input_controller;
  std::shared_ptr<MotionInputController> m_motion_input_controller;

  std::vector<std::shared_ptr<Controller>> m_controllers;
  std::vector<std::shared_ptr<SceneObject>> m_objects;
};

} // namespace Kononov
