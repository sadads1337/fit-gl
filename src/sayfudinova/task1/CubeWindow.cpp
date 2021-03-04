#include "CubeWindow.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>
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

constexpr std::array<GLuint, 34u> indices = {0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4,
                                             4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 6,
                                             6, 4, 0, 1, 1, 2, 2, 3, 7, 5};
} // namespace

void CubeWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/quad.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/quad.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);

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
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", changeColor);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(QVector3D), vertices.data(),
               GL_STATIC_DRAW);

  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);

  glEnableVertexAttribArray(posAttr_);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(uint), indices.data(),
               GL_STATIC_DRAW);

  glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    QColor color = QColorDialog::getColor();
    changeColor = QVector4D(color.red() / 255.0, color.green() / 255.0,
                            color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}