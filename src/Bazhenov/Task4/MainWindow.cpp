#include "MainWindow.hpp"

#include <algorithm>
#include <vector>
#include <cmath>

#include <QOpenGLShader>
#include <QVector4D>

namespace Bazhenov {

void MainWindow::initCube(GLfloat halfWidth, std::uint32_t factor) {
  Q_ASSERT(halfWidth >= 0);
  Q_ASSERT(factor >= 1U);

  if (arrayBuf_.isCreated())
    arrayBuf_.destroy();
  if (indexBuf_.isCreated())
    indexBuf_.destroy();

  arrayBuf_.create();
  indexBuf_.create();

  QVector<VertexData> vertices;
  QVector<GLuint> indices;

  for (auto face = 0U; face < 6; ++face) {
    // Add vertices
    const auto constCoord = face % 3;
    const auto coord1 = (face + 1) % 3;
    const auto coord2 = (face + 2) % 3;

    for (auto y = 0U; y < factor + 1; ++y) {
      for (auto x = 0U; x < factor + 1; ++x) {
        auto position = QVector3D{0, 0, 0};
        auto normal = QVector3D{0, 0, 0};
        auto texture = QVector2D{0, 0};
        auto tangent = QVector3D{0, 0, 0};
        auto bitangent = QVector3D{0, 0, 0};

        // int division is meant to be here!
        normal[constCoord] = static_cast<int>(face / 3 * 2) - 1;

        position[constCoord] = normal[constCoord] * halfWidth;
        position[coord1] = (x * 2.0F / factor - 1.0F) * halfWidth;
        position[coord2] =
            (y * 2.0F / factor - 1.0F) * halfWidth * normal[constCoord];

        texture.setX(static_cast<float>(x) / factor);
        texture.setY(static_cast<float>(y) / factor);

        tangent[coord1] = normal[constCoord];
        bitangent[coord2] = 1.0F;

        vertices.append({
            QVector3D{position.x(), position.y(), position.z()},
            QVector3D{normal.x(), normal.y(), normal.z()},
            QVector2D{texture.x(), texture.y()},
            QVector3D{tangent.x(), tangent.y(), tangent.z()},
            QVector3D{bitangent.x(), bitangent.y(), bitangent.z()},
        });
      }
    }

    // Add indices
    const auto faceIndexOffset = face * (factor + 1) * (factor + 1);
    for (auto y = 0U; y < factor; ++y) {
      const auto rowIndexOffset = (factor + 1) * y;

      indices.append(faceIndexOffset + rowIndexOffset);
      for (auto x = 0U; x < factor + 1; ++x) {
        indices.append(faceIndexOffset + rowIndexOffset + x);
        indices.append(faceIndexOffset + rowIndexOffset + x + (factor + 1));
      }
      indices.append(faceIndexOffset + rowIndexOffset + factor +
                        (factor + 1));
    }
  }

  arrayBuf_.bind();
  arrayBuf_.allocate(vertices.constData(), vertices.size() * sizeof(VertexData));

  indexBuf_.bind();
  indexBuf_.allocate(indices.constData(), indices.size() * sizeof(GLuint));
}

void MainWindow::initShaders() {
  program_->removeAllShaders();

  if (inputController_->getShader() == InputController::Shader::SHADER_PHONG) {
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/phong_vertex.glsl"))
      close();
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/phong_fragment.glsl"))
      close();
  }
  else if (inputController_->getShader() == InputController::Shader::SHADER_GOURAUD) {
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/gouraud_vertex.glsl"))
      close();
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/gouraud_fragment.glsl"))
      close();
  }

  if (!program_->link())
    close();
  if (!program_->bind())
    close();
}

void MainWindow::initTextures() {
  texture_ = std::make_unique<QOpenGLTexture>(QImage(":/Textures/glyphs.jpg").mirrored());
  normalMap_ = std::make_unique<QOpenGLTexture>(QImage(":/Textures/glyphs-normal.jpg").mirrored());

  texture_->setMinificationFilter(QOpenGLTexture::Nearest);
  normalMap_->setMinificationFilter(QOpenGLTexture::Nearest);

  texture_->setMagnificationFilter(QOpenGLTexture::Linear);
  normalMap_->setMagnificationFilter(QOpenGLTexture::Linear);

  texture_->setWrapMode(QOpenGLTexture::Repeat);
  normalMap_->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWindow::init() {
  constexpr QVector4D CLEAR_COLOR(0.25F, 0.25F, 0.375F, 1.0F);

  // Configure OpenGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(),
               CLEAR_COLOR.w());

  // Configure VBOs
  constexpr std::uint32_t VERTEX_MULTIPLICATION_FACTOR = 15;
  initCube(1.5F, VERTEX_MULTIPLICATION_FACTOR);

  // Configure program engines
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  inputController_ = std::make_shared<InputController>();

  // Configure shaders & textures
  initTextures();
  initShaders();
}

void MainWindow::render() {
  inputController_->update();

  arrayBuf_.bind();
  indexBuf_.bind();

  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Configure shaders, then launch rendering
  initShaders();

  QMatrix4x4 model_matrix;
  program_->setUniformValue("model_matrix", model_matrix);

  QMatrix4x4 view_matrix;
  view_matrix.translate(0.0F, 0.0F, -5.0F);
  view_matrix.rotate(inputController_->getRotation());
  program_->setUniformValue("view_matrix", view_matrix);

  constexpr GLfloat VERTICAL_ANGLE = 60.0F;
  constexpr GLfloat NEAR_PLANE = 0.1F;
  constexpr GLfloat FAR_PLANE = 100.0F;

  QMatrix4x4 projection_matrix;
  projection_matrix.perspective(VERTICAL_ANGLE, (GLfloat)width() / height(),
                         NEAR_PLANE, FAR_PLANE);
  program_->setUniformValue("projection_matrix", projection_matrix);

  auto time = static_cast<GLfloat>(frame_);
  if (inputController_->morphingIsOn())
    program_->setUniformValue("t", time);
  else // fixed cubic shape
    program_->setUniformValue("t", 0.0F);

  if (inputController_->lightIsOrbiting()) {
    auto light_position = QVector3D{9.0F * std::sin(time / 150.0F), 0.0F,
                                    -5.0F + 9.0F * std::cos(time / 150.0F)};
    program_->setUniformValue("light_position", light_position);
  }
  else
    program_->setUniformValue("light_position", QVector3D{6.5F, 0.0F, 1.5F});

  program_->setUniformValue("light_power", 1.0F);

  texture_->bind(0);
  program_->setUniformValue("texture", 0);

  normalMap_->bind(1);
  program_->setUniformValue("normal_map", 1);

  int offset = 0;
  auto vertex_position = program_->attributeLocation("vertex_position");
  program_->enableAttributeArray(vertex_position);
  program_->setAttributeBuffer(vertex_position, GL_FLOAT, offset, 3, sizeof(VertexData));

  offset += sizeof(QVector3D);
  auto vertex_normal = program_->attributeLocation("vertex_normal");
  program_->enableAttributeArray(vertex_normal);
  program_->setAttributeBuffer(vertex_normal, GL_FLOAT, offset, 3, sizeof(VertexData));

  offset += sizeof(QVector3D);
  auto vertex_texture = program_->attributeLocation("vertex_texture");
  program_->enableAttributeArray(vertex_texture);
  program_->setAttributeBuffer(vertex_texture, GL_FLOAT, offset, 2, sizeof(VertexData));

  offset += sizeof(QVector2D);
  auto vertex_tangent = program_->attributeLocation("vertex_tangent");
  program_->enableAttributeArray(vertex_tangent);
  program_->setAttributeBuffer(vertex_tangent, GL_FLOAT, offset, 3, sizeof(VertexData));

  offset += sizeof(QVector3D);
  auto vertex_bitangent = program_->attributeLocation("vertex_bitangent");
  program_->enableAttributeArray(vertex_bitangent);
  program_->setAttributeBuffer(vertex_bitangent, GL_FLOAT, offset, 3, sizeof(VertexData));

  glDrawElements(GL_QUAD_STRIP, indexBuf_.size(), GL_UNSIGNED_INT, nullptr);

  program_->disableAttributeArray(vertex_position);
  program_->disableAttributeArray(vertex_normal);
  program_->disableAttributeArray(vertex_texture);
  program_->disableAttributeArray(vertex_tangent);
  program_->disableAttributeArray(vertex_bitangent);

  program_->release();

  frame_++;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  inputController_->mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  inputController_->mouseMoveEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  inputController_->mouseReleaseEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  inputController_->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  inputController_->keyReleaseEvent(event);
}

} // namespace Bazhenov