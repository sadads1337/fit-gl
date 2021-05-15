#include "MainWindow.hpp"

#include <algorithm>
#include <vector>

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

void initCube(GLfloat halfWidth, std::uint32_t factor = 1U) {
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
        color.setRedF((x % 5 + y % 5 + face) % 4 / 3.0F);
        color.setGreenF((x % 5 + y % 5 + face + 3) % 4 / 3.0F);
        color.setBlueF((x % 5 + y % 5 + face + 6) % 4 / 3.0F);

        vertices.push_back(position.x());
        vertices.push_back(position.y());
        vertices.push_back(position.z());
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

void MainWindow::init() {
  // Configure OpenGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(),
               CLEAR_COLOR.w());

  // Configure VBOs
  initCube(1.0F, VERTEX_MULTIPLICATION_FACTOR);

  arrayBuf_.create();
  indexBuf_.create();

  arrayBuf_.bind();
  arrayBuf_.allocate(vertices.data(), static_cast<std::int32_t>(
                                          vertices.size() * sizeof(GLfloat)));

  indexBuf_.bind();
  indexBuf_.allocate(indices.data(), static_cast<std::int32_t>(indices.size() *
                                                               sizeof(GLuint)));

  // Configure shaders
  program_ = std::make_unique<QOpenGLShaderProgram>(this);

  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/vertex.glsl");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/fragment.glsl");

  program_->link();

  // Configure attributes and uniforms
  posAttr_ = program_->attributeLocation("vertex_position");
  normalAttr_ = program_->attributeLocation("vertex_normal");
  colAttr_ = program_->attributeLocation("vertex_color");

  matrixUniform_ = program_->uniformLocation("mvp_matrix");
  colFactorUniform_ = program_->uniformLocation("fragment_color_factor");
  offsetFromFaceUniform_ = program_->uniformLocation("offset_from_face");
  morphParamUniform_ = program_->uniformLocation("t");

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, VERTEX_POSITION_OFFSET, 3,
                               STRIDE * sizeof(GLfloat));
  program_->setAttributeBuffer(normalAttr_, GL_FLOAT, VERTEX_NORMAL_OFFSET, 3,
                               STRIDE * sizeof(GLfloat));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT, VERTEX_COLOR_OFFSET, 3,
                               STRIDE * sizeof(GLfloat));

  // Configure program engines
  inputController_ = std::make_shared<InputController>();
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
  program_->bind();

  QMatrix4x4 mvp_matrix;
  mvp_matrix.perspective(VERTICAL_ANGLE, (GLfloat)width() / height(),
                         NEAR_PLANE, FAR_PLANE);
  mvp_matrix.translate(0.0F, 0.0F, -5.0F);
  mvp_matrix.rotate(inputController_->getRotation());

  program_->setUniformValue(matrixUniform_, mvp_matrix);
  program_->setUniformValue(offsetFromFaceUniform_, 0.0F);
  program_->setUniformValue(colFactorUniform_, QMatrix4x4{});
  program_->setUniformValue(morphParamUniform_, static_cast<GLfloat>(frame_));

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

  glDrawElements(GL_QUAD_STRIP, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, nullptr);

  // Draw black lines

  arrayBuf_.bind();
  indexBuf_.bind();

  program_->setUniformValue(offsetFromFaceUniform_, 1.0e-3F);
  program_->setUniformValue(colFactorUniform_, QMatrix4x4{} * 0);

  glDrawElements(GL_LINE_STRIP, static_cast<GLsizei>(indices.size()),
                 GL_UNSIGNED_INT, nullptr);

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