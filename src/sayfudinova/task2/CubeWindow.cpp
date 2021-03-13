#include "CubeWindow.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>
#include <array>

namespace {
constexpr std::array<QVector3D, 8> vertices = {
    QVector3D(-0.5f, -0.5f, 0.5f),  // v0
    QVector3D(0.5f, -0.5f, 0.5f),   // v1
    QVector3D(-0.5f, 0.5f, 0.5f),   // v2
    QVector3D(0.5f, 0.5f, 0.5f),    // v3
    QVector3D(0.5f, -0.5f, -0.5f),  // v4
    QVector3D(0.5f, 0.5f, -0.5f),   // v5
    QVector3D(-0.5f, -0.5f, -0.5f), // v6
    QVector3D(-0.5f, 0.5f, -0.5f),  // v7
};

constexpr std::array<GLuint, 34u> indices = {0, 1, 2, 3, 3, 1, 1, 4, 3, 5, 5, 4,
                                             4, 6, 5, 7, 7, 6, 6, 0, 7, 2, 2, 6,
                                             6, 4, 0, 1, 1, 2, 2, 3, 7, 5};
} // namespace

void CubeWindow::init() {
  // Enable depth test and face culling
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Create VBO and IBO
  vbo.create();
  ibo.create();

  // Fill VBO
  vbo.bind();
  vbo.allocate(vertices.data(),
               static_cast<std::int32_t>(vertices.size() * sizeof(QVector3D)));

  // Fill IBO
  ibo.bind();
  ibo.allocate(indices.data(),
               static_cast<std::int32_t>(indices.size() * sizeof(GLuint)));

  // Configure shaders
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/quad.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/quad.fs");
  program_->link();

  // Configure attributes and uniforms
  posAttr_ = program_->attributeLocation("posAttr");
  matrixUniform_ = program_->uniformLocation("matrix");
}

void CubeWindow::render() {
  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // Clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Calculate MVP
  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

  // Bind shader and set attrs and unis
  program_->bind();
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", changeColor);
  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
  program_->enableAttributeArray(posAttr_);

  // Bind buffers
  vbo.bind();
  ibo.bind();

  // Draw
  glDrawElements(GL_TRIANGLE_STRIP, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, nullptr);

  // Release all and increase counter
  program_->disableAttributeArray(posAttr_);
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
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;

  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}