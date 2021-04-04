

#include "cubewidget.hpp"

#include <QMouseEvent>

#include <utility>

CubeWidget::CubeWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void CubeWidget::setMorphFactor(float val) {
  morphFactor = val;
  update();
}

void CubeWidget::setColor(const QColor &color) {
  if (mode_ == colorMode::face) {
    pCube_->setFaceColor(color, currentFace_);
  } else {
    pCube_->setEdgeColor(color, currentFace_);
  }
}

void CubeWidget::setCurrentFace(int face) { currentFace_ = face; }

void CubeWidget::setFaceMode() { mode_ = colorMode::face; }

void CubeWidget::setEdgeMode() { mode_ = colorMode::edge; }

void CubeWidget::makeNewGrid(int grid_steps) {
  auto newCube = std::make_unique<Cube>(grid_steps, initSize, initFaceColor,
                                        initEdgeColor);
  pCube_ = std::move(newCube);
}

void CubeWidget::mousePressEvent(QMouseEvent *e) {
  mouseLastPosition = mousePressPosition = QVector2D(e->pos());
  if (e->button() == Qt::RightButton) {
    angularSpeed = 0;
  }
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    QVector2D diff = QVector2D(e->pos()) - mousePressPosition;
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    qreal acc = diff.length() / 100.0;

    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
    angularSpeed += acc;
  }
}

void CubeWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::RightButton) {
    QVector2D diff = QVector2D(event->pos()) - mouseLastPosition;
    rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    qreal angle = diff.length() / 8.0;
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
  }
  mouseLastPosition = QVector2D(event->pos());
}

void CubeWidget::wheelEvent(QWheelEvent *ev) {
  auto angle = ev->angleDelta().y();

  projection.translate(0.f, 0.f, angle / (8. * 50.));
}

void CubeWidget::timerEvent(QTimerEvent *) {
  angularSpeed *= 0.99;
  if (angularSpeed < 0.01) {
    angularSpeed = 0.0;
  } else {
    rotation =
        QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
  }
  update();
}

QSize CubeWidget::minimumSizeHint() const { return {640, 480}; }

void CubeWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.9f, 0.9f, 0.9f, 1.f);
  initShaders();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  auto newCube =
      std::make_unique<Cube>(initSteps, initSize, initFaceColor, initEdgeColor);
  pCube_ = std::move(newCube);

  timer.start(16, this);
}

void CubeWidget::initShaders() {
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                       ":/vshader.glsl")) {
    close();
  }
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/fshader.glsl")) {
    close();
  }
  if (!program.link()) {
    close();
  }
  if (!program.bind()) {
    close();
  }
}

void CubeWidget::resizeGL(const int w, const int h) {
  float aspect = qreal(w) / qreal(h ? h : 1);
  const float zNear = 0.1f, zFar = 100.f, fov = 60.f;

  projection.setToIdentity();
  projection.perspective(fov, aspect, zNear, zFar);
}

void CubeWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Calculate model view transformation
  QMatrix4x4 matrix;
  matrix.translate(0.0, 0.0, zDistance);
  matrix.rotate(rotation);

  program.setUniformValue("mvp_matrix", projection * matrix);
  program.setUniformValue("morphFactor", morphFactor);

  pCube_->draw(program);
}
