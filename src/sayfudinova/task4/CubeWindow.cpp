#include "CubeWindow.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <QImage>
#include <array>

namespace fgl {

struct VertexData {
  QVector3D position;
  QVector3D normal;
  QVector2D texture;
  QVector3D tangent;
};

void CubeWindow::initCube(float width, int N) {
  Q_ASSERT(N > 1);

  auto halfWidth = width / 2.0f;
  auto step = width / float(N - 1);
  auto textStep = 1.0f / float(N - 1);

  std::vector<VertexData> vertices;
  for (auto z = -1; z <= 1; z += 2) {
    for (auto j = 0; j < N; j++) {
      for (auto i = 0; i < N; i++) {
        vertices.emplace_back(VertexData{
            QVector3D(z * (-halfWidth + i * step), -halfWidth + j * step,
                      z * halfWidth),
            QVector3D(0.0, 0.0, z), QVector2D(i * textStep, j * textStep),
            QVector3D(z, 0.0, 0.0)});
      }
    }
  }
  for (auto x = -1; x <= 1; x += 2) {
    for (auto k = 0; k < N; k++) {
      for (auto j = 0; j < N; j++) {
        vertices.emplace_back(VertexData{
            QVector3D(x * halfWidth, -halfWidth + j * step,
                      x * (-halfWidth + k * step)),
            QVector3D(x, 0.0, 0.0), QVector2D(j * textStep, k * textStep),
            QVector3D(0.0, 1.0, 0.0)});
      }
    }
  }
  for (auto y = -1; y <= 1; y += 2) {
    for (auto i = 0; i < N; i++) {
      for (auto k = 0; k < N; k++) {
        vertices.emplace_back(VertexData{
            QVector3D(-halfWidth + i * step, y * halfWidth,
                      y * (-halfWidth + k * step)),
            QVector3D(0.0, y, 0.0), QVector2D(k * textStep, i * textStep),
            QVector3D(0.0, y, 0.0)});
      }
    }
  }

  std::vector<GLuint> indices;
  for (int i = 0; i < 6 * N * N; i += N * N) {
    for (int j = 0; j < (N - 1) * (N - 1); j += N) {
      for (int k = 0; k < (N - 1); k++) {
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
  vbo_.allocate(vertices.data(),
                static_cast<int>(vertices.size() * sizeof(VertexData)));

  ibo_.create();
  ibo_.bind();
  ibo_.allocate(indices.data(),
                static_cast<int>(indices.size() * sizeof(GLuint)));
}

void CubeWindow::initText() {
  texture_ = std::make_shared<QOpenGLTexture>(
      QImage(":/textures/brickwall.jpg").mirrored());
  normalMap_ = std::make_shared<QOpenGLTexture>(
      QImage(":/textures/brickwall_normal.jpg").mirrored());

  texture_->setMinificationFilter(QOpenGLTexture::Nearest);
  texture_->setMagnificationFilter(QOpenGLTexture::Linear);
  texture_->setWrapMode(QOpenGLTexture::Repeat);

  normalMap_->setMinificationFilter(QOpenGLTexture::Nearest);
  normalMap_->setMagnificationFilter(QOpenGLTexture::Linear);
  normalMap_->setWrapMode(QOpenGLTexture::Repeat);
}

void CubeWindow::init() {
  // Enable depth test and face culling
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Configure shaders
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/quad.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/quad.fs");
  program_->link();

  // Configure attributes and uniforms
  posAttr_ = program_->attributeLocation("posAttr");
  normAttr_ = program_->attributeLocation("normAttr");
  textureAttr_ = program_->attributeLocation("textureAttr");
  tangentAttr_ = program_->attributeLocation("tangentAttr");

  initText();
  initCube(2.0f, 2U);

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(VertexData));
  program_->setAttributeBuffer(normAttr_, GL_FLOAT, sizeof(QVector3D), 3,
                               sizeof(VertexData));
  program_->setAttributeBuffer(textureAttr_, GL_FLOAT, 2 * sizeof(QVector3D), 2,
                               sizeof(VertexData));
  program_->setAttributeBuffer(tangentAttr_, GL_FLOAT,
                               2 * sizeof(QVector3D) + sizeof(QVector2D), 3,
                               sizeof(VertexData));
}

void CubeWindow::render() {
  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Bind shader
  program_->bind();

  // Calculate MVP
  QMatrix4x4 matrix;
  QMatrix4x4 model;
  matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);

  matrix.translate(0, 0, -2);
  matrix.rotate(15.0 * frame_ / screen()->refreshRate(), rotationAxis_);
  matrix.scale(0.5f, 0.5f, 0.5f);

  model.translate(0, 0, -2);
  model.rotate(15.0 * frame_ / screen()->refreshRate(), rotationAxis_);
  model.scale(0.5f, 0.5f, 0.5f);

  // Set attrs and unis
  program_->setUniformValue("matrix", matrix);
  program_->setUniformValue("model", model);
  program_->setUniformValue("normal_matrix", model.normalMatrix());

  texture_->bind(0);
  program_->setUniformValue("samplerText", 0);

  normalMap_->bind(1);
  program_->setUniformValue("samplerNormMap", 1);

  vbo_.bind();

  program_->enableAttributeArray(normAttr_);
  program_->enableAttributeArray(posAttr_);
  program_->enableAttributeArray(textureAttr_);
  program_->enableAttributeArray(tangentAttr_);

  ibo_.bind();

  // Draw
  glDrawElements(GL_TRIANGLES, ibo_.size(), GL_UNSIGNED_INT, nullptr);

  program_->disableAttributeArray(posAttr_);
  program_->disableAttributeArray(normAttr_);
  program_->disableAttributeArray(textureAttr_);
  program_->disableAttributeArray(tangentAttr_);

  // Release all and increase counter
  program_->release();
  ++frame_;
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  mousePressPosition_ = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(event->localPos()) - mousePressPosition_;

  rotationAxis_ = QVector3D(diff.y(), diff.x(), 0.0f).normalized();
}
} // namespace fgl