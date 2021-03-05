#include "SquareWindow.hpp"

#include <QScreen>

#include <QColorDialog>

#include <array>

namespace {

constexpr std::array<QVector3D, 8u> vertices = {
    QVector3D(-0.7f, -0.7f, 0.7f),  QVector3D(0.7f, -0.7f, 0.7f),
    QVector3D(-0.7f, 0.7f, 0.7f),   QVector3D(0.7f, 0.7f, 0.7f),
    QVector3D(0.7f, -0.7f, -0.7f),  QVector3D(0.7f, 0.7f, -0.7f),
    QVector3D(-0.7f, -0.7f, -0.7f), QVector3D(-0.7f, 0.7f, -0.7f)};

constexpr std::array<GLuint, 34u> indicies = {
    0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4, 4, 6, 5, 7, 7,
    6, 6, 0, 7, 2, 2, 6, 6, 4, 0, 1, 1, 2, 2, 3, 7, 5};

} // namespace

namespace fgl {

void SquareWindow::init() {
  array_buffer_.create();
  array_buffer_.bind();
  array_buffer_.allocate(
      vertices.data(),
      static_cast<std::int32_t>(vertices.size() * sizeof(QVector3D)));

  index_buffer_.create();
  index_buffer_.bind();
  index_buffer_.allocate(
      indicies.data(),
      static_cast<std::int32_t>(indicies.size() * sizeof(GLuint)));
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/square.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/square.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  Q_ASSERT(posAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  Q_ASSERT(matrixUniform_ != -1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void SquareWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  program_->bind();

  // rotation
  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", square_color);

  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), nullptr);
  glEnableVertexAttribArray(posAttr_);

  array_buffer_.bind();
  index_buffer_.bind();
  glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indicies.size()), GL_UNSIGNED_INT, nullptr);
  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}

void SquareWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void SquareWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference
  // vector
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}

void SquareWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_C) {
    const auto color = QColorDialog::getColor();
    square_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                             color.blue() / 255.0, 1);
  }
}

} // namespace fgl