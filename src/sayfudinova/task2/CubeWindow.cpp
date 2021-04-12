#include "CubeWindow.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>

void CubeWindow::initCube(float width, int N) {
  if (N <= 1)
    throw std::invalid_argument("The number of parts cannot be less than 1");

  auto halfWidth = width / 2.f;
  auto step = width / (static_cast<float>(N) - 1.f);

  std::vector<QVector3D> vertices;

  for (auto z = -1; z <= 1; z += 2) {
    for (auto y = 0; y < N; y++) {
      for (auto x = 0; x < N; x++) {
        vertices.emplace_back(QVector3D(z * (-halfWidth + x * step),
                                  -halfWidth + y * step, z * halfWidth));
      }
    }
  }
  for (auto x = -1; x <= 1; x += 2) {
    for (auto z = 0; z < N; z++) {
      for (auto y = 0; y < N; y++) {
        vertices.emplace_back(QVector3D(x * halfWidth, -halfWidth + y * step,
                                  x * (-halfWidth + z * step)));
      }
    }
  }
  for (auto y = -1; y <= 1; y += 2) {
    for (auto x = 0; x < N; x++) {
      for (auto z = 0; z < N; z++) {
        vertices.emplace_back(QVector3D(-halfWidth + x * step, y * halfWidth,
                                  y * (-halfWidth + z * step)));
      }
    }
  }

  std::vector<GLuint> indices;
  for (auto i = 0; i < 6 * N * N; i += N * N) {
    for (auto j = 0; j < (N - 1) * (N - 1); j += N) {
      for (auto k = 0; k < (N - 1); k++) {
        indices.emplace_back(i + j + k + N);
        indices.emplace_back(i + j + k + 0);
        indices.emplace_back(i + j + k + N + 1);
        indices.emplace_back(i + j + k + N + 1);
        indices.emplace_back(i + j + k + 0);
        indices.emplace_back(i + j + k + 1);
      }
    }
  }

  vbo_.create();
  vbo_.bind();
  vbo_.allocate(vertices.data(), static_cast<GLsizei>((vertices.size() * sizeof(QVector3D))));

  ibo_.create();
  ibo_.bind();
  ibo_.allocate(indices.data(), static_cast<GLsizei>(indices.size() * sizeof(GLuint)));
}

void CubeWindow::init() {
  // Enable depth test and face culling
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  start_ = std::chrono::system_clock::now();

  initCube(2.f, 15U);

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
  time_ = std::chrono::system_clock::now() - start_;

  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // Clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Calculate MVP
  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis_);
  matrix.scale(0.6f, 0.6f, 0.6f);

  // Bind shader and set attrs and unis
  program_->bind();
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", changeColor_);
  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(QVector3D));
  program_->enableAttributeArray(posAttr_);

  program_->setUniformValue("time", time_.count());
  program_->setUniformValue("flag", 1);

  program_->bind();

  glDrawElements(GL_TRIANGLE_STRIP, ibo_.size(), GL_UNSIGNED_SHORT, nullptr);

  program_->setUniformValue("flag", 0);
  program_->bind();

  glDrawElements(GL_LINES, ibo_.size(), GL_UNSIGNED_INT, nullptr);

  // Release all and increase counter
  program_->disableAttributeArray(posAttr_);
  program_->release();
  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    changeColor_ = QVector4D(color.red() / 255.0, color.green() / 255.0,
                             color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  mousePressPosition_ = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(event->localPos()) - mousePressPosition_;
  rotationAxis_ = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}