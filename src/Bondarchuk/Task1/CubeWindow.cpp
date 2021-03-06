#include "CubeWindow.hpp"
#include <QApplication>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_0_Core>
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
constexpr std::array<GLuint, 34u> indexes = {0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4,
                                             4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 6,
                                             6, 4, 0, 1, 1, 2, 2, 3, 7, 5};

constexpr std::array<GLuint, 24u> lineindexes = {
    0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4, 4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 0};

} // namespace

namespace fgl {

void CubeWindow::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  vbo.create();
  ibo.create();

  vbo.bind();
  vbo.allocate(vertices.data(),
               static_cast<std::int32_t>(vertices.size() * sizeof(QVector3D)));

  ibo.bind();
  ibo.allocate(indexes.data(),
               static_cast<std::int32_t>(indexes.size() * sizeof(GLuint)));

  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/cube.fs");
  program_->link();

  posAttr_ = program_->attributeLocation("posAttr");
  matrixUniform_ = program_->uniformLocation("matrix");


}

void CubeWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);

  program_->bind();
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", cube_color);
  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  program_->enableAttributeArray(posAttr_);

  vbo.bind();
  ibo.bind();

  glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indexes.size()),
                 GL_UNSIGNED_INT, nullptr);

  

  program_->disableAttributeArray(posAttr_);
  program_->release();

  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    cube_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                           color.blue() / 255.0, 1);
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
