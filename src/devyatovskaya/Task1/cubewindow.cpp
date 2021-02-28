#include "cubewindow.h"
#include <QMouseEvent>
#include <QOpenGLFunctions>

#include <QScreen>

namespace fgl {
void CubeWindow::setRotation() {
  angular_speed_ *= 0.99;

  if (angular_speed_ < 0.01) {
    angular_speed_ = 0.0;
  } else {
    rotation_ = QQuaternion::fromAxisAndAngle(rotation_axis_, angular_speed_) *
                rotation_;
  }
}

void CubeWindow::initColorDialog() {
  color_dialog_.setGeometry(50, 50, 100, 100);
  color_dialog_.show();
  color_dialog_.setOption(QColorDialog::NoButtons);
}

void CubeWindow::initSlidersDialog() {
  slider_x_.setOrientation(Qt::Orientation::Horizontal);
  slider_y_.setOrientation(Qt::Orientation::Horizontal);
  slider_z_.setOrientation(Qt::Orientation::Horizontal);
  slider_x_.setGeometry(50, 217, 230, 50);
  slider_y_.setGeometry(50, 234, 230, 50);
  slider_z_.setGeometry(50, 251, 230, 50);
}

void CubeWindow::mousePressEvent(QMouseEvent *e) {
  mouse_press_position_ = QVector2D(e->screenPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *e) {
  QVector2D diff = QVector2D(e->screenPos()) - mouse_press_position_;
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  qreal acc = diff.length() / 100.0f;

  rotation_axis_ = (rotation_axis_ * angular_speed_ + n * acc).normalized();
  angular_speed_ += acc;
}

void CubeWindow::init() {
  program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                   ":/Shaders/vshader.vs");
  program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                   ":/Shaders/fshader.fs");
  program_.link();

  initializeOpenGLFunctions();
  initColorDialog();
  initSlidersDialog();

  const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());
  glViewport(0, 0, width() * retina_scale, height() * retina_scale);

  glClearColor(0.1f, 0.3f, 0.3f, 1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void CubeWindow::render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_.bind();

  QMatrix4x4 matrix;
  resizeGL();
  setRotation();
  matrix.translate(0.0, 0.0, -3.0);

  matrix.rotate(rotation_);

  const auto matrix_location = program_.uniformLocation("matrix");
  Q_ASSERT(matrix_location != -1);

  program_.setUniformValue(matrix_location, projection_ * matrix);

  glDepthFunc(GL_LESS);
  glCullFace(GL_BACK);

  painter_.setUniformColor(color_dialog_.currentColor());

  cube_geometry_.DrawGeometry(&program_);
  edges_geometry_.DrawGeometry(&program_);

  program_.release();
  ++frame_;
}

void CubeWindow::resizeGL() {
  const auto ratio = static_cast<float>(width()) / static_cast<float>(height());
  const auto near_plane = 0.1f, far_plane = 100.0f, fov = 45.0f;

  projection_.setToIdentity();
  projection_.perspective(fov, ratio, near_plane, far_plane);
}

} // namespace fgl
