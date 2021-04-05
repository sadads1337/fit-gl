#include "SceneWindow.hpp"

#include <QScreen>

namespace Kononov {

void SceneWindow::init() {
  /*
   * Logger initialization
   */
  m_logger = std::make_unique<QOpenGLDebugLogger>(this);

  connect(m_logger.get(), &QOpenGLDebugLogger::messageLogged, this,
          &SceneWindow::onMessageLogged);
  if (m_logger->initialize()) {
    m_logger->startLogging(QOpenGLDebugLogger::SynchronousLogging);
    m_logger->enableMessages();
  }

  /*
   * Init objects
   */
  m_camera = std::make_shared<Camera>();

  m_direction_input_controller = std::make_shared<DirectionInputController>();
  m_direction_input_controller->setObject(m_camera);
  m_controllers.push_back(m_direction_input_controller);

  m_motion_input_controller = std::make_shared<MotionInputController>();
  m_motion_input_controller->setObject(m_camera);
  m_motion_input_controller->setDirectionSource(m_direction_input_controller);
  m_controllers.push_back(m_motion_input_controller);
}

void SceneWindow::render() {
  const float delta = 1.0F / static_cast<float>(screen()->refreshRate());
  for (const auto &c : getControllers()) {
    c->update(delta);
  }

  // NOLINTNEXTLINE(hicpp-signed-bitwise)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const auto pixel_ratio = devicePixelRatio();
  const auto ratio = static_cast<float>(width()) / static_cast<float>(height());
  m_camera->setPerspective(m_fov, ratio, m_near, m_far);
  m_camera->beginRender((GLsizei)(width() * pixel_ratio),
                        (GLsizei)(height() * pixel_ratio));

  for (const auto &obj : m_objects) {
    obj->render(*getCamera());
  }
}

void SceneWindow::mousePressEvent(QMouseEvent *event) {
  m_direction_input_controller->mousePressEvent(event);
}

void SceneWindow::mouseMoveEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseMoveEvent(event);
}

void SceneWindow::mouseReleaseEvent(QMouseEvent *event) {
  m_direction_input_controller->mouseReleaseEvent(event);
}

void SceneWindow::keyPressEvent(QKeyEvent *event) {
  m_motion_input_controller->keyPressEvent(event);
}

void SceneWindow::keyReleaseEvent(QKeyEvent *event) {
  m_motion_input_controller->keyReleaseEvent(event);
}

void SceneWindow::onMessageLogged(const QOpenGLDebugMessage &message) {
  qDebug() << message;
}

std::shared_ptr<Camera> &SceneWindow::getCamera() { return m_camera; }

std::shared_ptr<DirectionInputController> &
SceneWindow::getDirectionInputController() {
  return m_direction_input_controller;
}

std::shared_ptr<MotionInputController> &
SceneWindow::getMotionInputController() {
  return m_motion_input_controller;
}

std::vector<std::shared_ptr<Controller>> &SceneWindow::getControllers() {
  return m_controllers;
}

std::vector<std::shared_ptr<SceneObject>> &SceneWindow::getObjects() {
  return m_objects;
}

float SceneWindow::getFov() const { return m_fov; }
void SceneWindow::setFov(float fov) { m_fov = fov; }
float SceneWindow::getNear() const { return m_near; }
void SceneWindow::setNear(float near) { m_near = near; }
float SceneWindow::getFar() const { return m_far; }
void SceneWindow::setFar(float far) { m_far = far; }

} // namespace Kononov