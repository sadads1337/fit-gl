#include "CubeWindow.hpp"
#include <QOpenGLFunctions_4_0_Core>
#include <QApplication>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QRgb>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>




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
/*0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4, 4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 0*/
 constexpr std::array<GLuint, 34u> indexes = {
    0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4, 4, 6, 5, 7, 7,
    6, 6, 0, 7, 2, 2, 6, 6, 4, 0, 1, 1, 2, 2, 3, 7, 5};


} // namespace

namespace fgl {

void CubeWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/cube.fs");
  program_->link();

  posAttr_ = program_->attributeLocation("posAttr");
  colAttr_ = program_->attributeLocation("colAttr");
  matrixUniform_ = program_->uniformLocation("matrix");
 

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void CubeWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);

  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", cube_color);

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(QVector3D), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);

  

  unsigned int ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(unsigned int), indexes.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

  glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, nullptr);

 

  glDisableVertexAttribArray(posAttr_);
  glDisableVertexAttribArray(colAttr_);

  program_->release();

  ++frame_;
}


void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    cube_color = QVector4D(color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  mousePressPosition = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  const auto diff = QVector2D(event->localPos()) - mousePressPosition;
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}



} // namespace fgl