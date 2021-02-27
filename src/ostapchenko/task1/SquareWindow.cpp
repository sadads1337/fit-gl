#include "SquareWindow.h"

#include <QOpenGLFunctions>
#include <QScreen>

#include <QColorDialog>
#include <QMouseEvent>

#include <array>
#include <cassert>

namespace {

constexpr std::array<QVector3D, 8u> vertices = {

    QVector3D(-0.5f, -0.5f, 0.5f),  // v0
    QVector3D(0.5f, -0.5f, 0.5f),   // v1
    QVector3D(-0.5f, 0.5f, 0.5f),   // v2
    QVector3D(0.5f, 0.5f, 0.5f),    // v3
    QVector3D(0.5f, -0.5f, -0.5f),  // v4
    QVector3D(0.5f, 0.5f, -0.5f),   // v5
    QVector3D(-0.5f, -0.5f, -0.5f), // v6
    QVector3D(-0.5f, 0.5f, -0.5f)   // v7
};

constexpr std::array<GLuint, 34u> v_indicies = {
    0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4, 4, 6, 5, 7, 7,
    6, 6, 0, 7, 2, 2, 6, 6, 4, 0, 1, 1, 2, 2, 3, 7, 5};

} // namespace

namespace fgl {

void SquareWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/square.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/square.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);

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

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(QVector3D), vertices.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);
  glEnableVertexAttribArray(posAttr_);

  unsigned int v_ibo;
  glGenBuffers(1, &v_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(unsigned int),
               v_indicies.data(), GL_STATIC_DRAW);

  glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, nullptr);
  // glDisableVertexAttribArray(colAttr_);
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
  QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference
  // vector
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}

void SquareWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    QColor color = QColorDialog::getColor();
    square_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                             color.blue() / 255.0, 1);
  }
}

} // namespace fgl