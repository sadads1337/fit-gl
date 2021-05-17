#include "MainWindow.hpp"

#include <algorithm>
#include <vector>
#include <cmath>

#include <QOpenGLShader>
#include <QVector4D>

namespace Bazhenov {

constexpr std::uint32_t STRIDE = 9;
constexpr std::uint32_t VERTEX_POSITION_OFFSET = 0;
constexpr std::uint32_t VERTEX_NORMAL_OFFSET = 3;
constexpr std::uint32_t VERTEX_COLOR_OFFSET = 6;

constexpr std::uint32_t VERTEX_MULTIPLICATION_FACTOR = 15;

std::vector<GLfloat> vertices;
std::vector<GLuint> indices;

constexpr GLfloat VERTICAL_ANGLE = 60.0F;
constexpr GLfloat NEAR_PLANE = 0.1F;
constexpr GLfloat FAR_PLANE = 100.0F;

constexpr QVector4D CLEAR_COLOR(0.25F, 0.25F, 0.375F, 1.0F);

void initCube(QVector3D offset, GLfloat halfWidth, std::uint32_t factor = 1U) {
  Q_ASSERT(halfWidth >= 0);
  Q_ASSERT(factor >= 1U);

  for (auto face = 0U; face < 6; ++face) {
    // Add vertices
    const auto constCoord = face % 3;
    const auto coord1 = (face + 1) % 3;
    const auto coord2 = (face + 2) % 3;

    for (auto y = 0U; y < factor + 1; ++y) {
      for (auto x = 0U; x < factor + 1; ++x) {
        auto position = QVector3D{0, 0, 0};
        auto normal = QVector3D{0, 0, 0};

        // int division is meant to be here!
        normal[constCoord] = static_cast<int>(face / 3 * 2) - 1;

        position[constCoord] = normal[constCoord] * halfWidth;
        position[coord1] = (x * 2.0F / factor - 1.0F) * halfWidth;
        position[coord2] =
            (y * 2.0F / factor - 1.0F) * halfWidth * normal[constCoord];

        auto color = QColor{};
        color.setRedF(0.5F);
        color.setGreenF(0.5F);
        color.setBlueF(0.5F);

        vertices.push_back(position.x() + offset.x());
        vertices.push_back(position.y() + offset.y());
        vertices.push_back(position.z() + offset.z());
        vertices.push_back(normal.x());
        vertices.push_back(normal.y());
        vertices.push_back(normal.z());
        vertices.push_back(color.redF());
        vertices.push_back(color.greenF());
        vertices.push_back(color.blueF());
      }
    }

    // Add indices
    const auto faceIndexOffset = face * (factor + 1) * (factor + 1);
    for (auto y = 0U; y < factor; ++y) {
      const auto rowIndexOffset = (factor + 1) * y;

      indices.push_back(faceIndexOffset + rowIndexOffset);
      for (auto x = 0U; x < factor + 1; ++x) {
        indices.push_back(faceIndexOffset + rowIndexOffset + x);
        indices.push_back(faceIndexOffset + rowIndexOffset + x + (factor + 1));
      }
      indices.push_back(faceIndexOffset + rowIndexOffset + factor +
                        (factor + 1));
    }
  }
}

} // namespace Bazhenov

namespace Bazhenov {

void MainWindow::initShaders() {
  program_->removeAllShaders();

  if (inputController_->getShader() == InputController::SHADER_PHONG) {
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/phong_vertex.glsl"))
      close();
    if (!program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/phong_fragment.glsl"))
      close();
  }
  else if (inputController_->getShader() == InputController::SHADER_GOURAUD) {
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

void MainWindow::init() {
  // Configure OpenGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(),
               CLEAR_COLOR.w());

  // Configure VBOs
  initCube({0.0F, 0.0F, 0.0F}, 0.5F, VERTEX_MULTIPLICATION_FACTOR);

  arrayBuf_.create();
  indexBuf_.create();

  arrayBuf_.bind();
  arrayBuf_.allocate(vertices.data(), static_cast<std::int32_t>(
                                          vertices.size() * sizeof(GLfloat)));

  indexBuf_.bind();
  indexBuf_.allocate(indices.data(), static_cast<std::int32_t>(indices.size() *
                                                               sizeof(GLuint)));

  // Configure program engines
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  inputController_ = std::make_shared<InputController>();

  // Configure shaders
  initShaders();

  // Configure attributes and uniforms
  const auto posAttr_ = program_->attributeLocation("vertex_position");
  const auto normalAttr_ = program_->attributeLocation("vertex_normal");
  const auto colAttr_ = program_->attributeLocation("vertex_color");

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, VERTEX_POSITION_OFFSET, 3,
                               STRIDE * sizeof(GLfloat));
  program_->setAttributeBuffer(normalAttr_, GL_FLOAT, VERTEX_NORMAL_OFFSET, 3,
                               STRIDE * sizeof(GLfloat));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT, VERTEX_COLOR_OFFSET, 3,
                               STRIDE * sizeof(GLfloat));
}

void MainWindow::render() {
  // Handle color selection
  inputController_->update();
  bool newColorSelected = inputController_->destructiveCheckNewColorSelected();

  arrayBuf_.bind();

  if (newColorSelected) {
    const auto newColor = inputController_->getColor();
    for (auto i = 0U; i < vertices.size() / STRIDE; ++i) {
      const auto redI = STRIDE * i + VERTEX_COLOR_OFFSET;
      const auto greenI = STRIDE * i + VERTEX_COLOR_OFFSET + 1;
      const auto blueI = STRIDE * i + VERTEX_COLOR_OFFSET + 2;

      vertices[redI] = 0.5F * (vertices[redI] + newColor.redF());
      vertices[greenI] = 0.5F * (vertices[greenI] + newColor.greenF());
      vertices[blueI] = 0.5F * (vertices[blueI] + newColor.blueF());
    }

    arrayBuf_.allocate(vertices.data(), static_cast<std::int32_t>(
                                            vertices.size() * sizeof(GLfloat)));
  }

  indexBuf_.bind();

  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Configure shaders, then launch rendering
  initShaders();

  QMatrix4x4 view_matrix;
  view_matrix.translate(0.0F, 0.0F, -5.0F);
  view_matrix.rotate(inputController_->getRotation());
  program_->setUniformValue("view_matrix", view_matrix);

  QMatrix4x4 projection_matrix;
  projection_matrix.perspective(VERTICAL_ANGLE, (GLfloat)width() / height(),
                         NEAR_PLANE, FAR_PLANE);
  program_->setUniformValue("projection_matrix", projection_matrix);

  program_->setUniformValue("offset_from_face", 0.0F);
  program_->setUniformValue("fragment_color_factor", 1.0F);

  auto time = static_cast<GLfloat>(frame_);
  if (inputController_->morphingIsOn())
    program_->setUniformValue("t", time);
  else
    program_->setUniformValue("t", 0.0F);

  if (inputController_->lightIsOrbiting()) {
    auto light_position = QVector3D{9.0F * std::sin(time / 150.0F), 0.0F,
                                    -5.0F + 9.0F * std::cos(time / 150.0F)};
    program_->setUniformValue("light_position", light_position);
  }
  else
    program_->setUniformValue("light_position", QVector3D{6.5F, 0.0F, 1.5F});

  program_->setUniformValue("light_power", 1.0F);

  const auto posAttr_ = program_->attributeLocation("vertex_position");
  const auto normalAttr_ = program_->attributeLocation("vertex_normal");
  const auto colAttr_ = program_->attributeLocation("vertex_color");

  program_->setAttributeArray(
      posAttr_, GL_FLOAT,
      reinterpret_cast<void *>(VERTEX_POSITION_OFFSET * sizeof(GLfloat)), 3,
      STRIDE * sizeof(GLfloat));
  program_->setAttributeArray(
      normalAttr_, GL_FLOAT,
      reinterpret_cast<void *>(VERTEX_NORMAL_OFFSET * sizeof(GLfloat)), 3,
      STRIDE * sizeof(GLfloat));
  program_->setAttributeArray(
      colAttr_, GL_FLOAT,
      reinterpret_cast<void *>(VERTEX_COLOR_OFFSET * sizeof(GLfloat)), 3,
      STRIDE * sizeof(GLfloat));

  program_->enableAttributeArray(posAttr_);
  program_->enableAttributeArray(normalAttr_);
  program_->enableAttributeArray(colAttr_);

  for (int x = -1; x <= 1; ++x) {
    for (int y = -1; y <= 1; ++y) {
      for (int z = -1; z <= 1; ++z) {
        arrayBuf_.bind();
        indexBuf_.bind();

        QMatrix4x4 model_matrix;
        model_matrix.translate(x * 1.5F, y * 1.5F, z * 1.5F);
        program_->setUniformValue("model_matrix", model_matrix);

        glDrawElements(GL_QUAD_STRIP, static_cast<GLsizei>(indices.size()),
                       GL_UNSIGNED_INT, nullptr);
      }
    }
  }

  program_->disableAttributeArray(colAttr_);
  program_->disableAttributeArray(normalAttr_);
  program_->disableAttributeArray(posAttr_);

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