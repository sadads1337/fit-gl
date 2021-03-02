#include "MainWindow.hpp"

#include <QOpenGLShader>
#include <QVector4D>

namespace Bazhenov {

constexpr std::uint32_t STRIDE = 9;
constexpr std::uint32_t VERTEX_POSITION_OFFSET = 0;
constexpr std::uint32_t VERTEX_COLOR_OFFSET = 6;

std::array<GLfloat, 6 * 4 *STRIDE> vertices = {
    // Vertex data for face 0
    -1.0F, -1.0F, 1.0F, 0, 0, 1, 0.0F, 0.0F, 0.0F,  // v0
    1.0F, -1.0F, 1.0F, 0, 0, 1, 0.333F, 0.0F, 0.0F, // v1
    -1.0F, 1.0F, 1.0F, 0, 0, 1, 0.0F, 0.5F, 0.0F,   // v2
    1.0F, 1.0F, 1.0F, 0, 0, 1, 0.333F, 0.5F, 0.0F,  // v3

    // Vertex data for face 1
    1.0F, -1.0F, 1.0F, 1, 0, 0, 0.0F, 0.5F, 0.0F,    // v4
    1.0F, -1.0F, -1.0F, 1, 0, 0, 0.333F, 0.5F, 0.0F, // v5
    1.0F, 1.0F, 1.0F, 1, 0, 0, 0.0F, 1.0F, 0.0F,     // v6
    1.0F, 1.0F, -1.0F, 1, 0, 0, 0.333F, 1.0F, 0.0F,  // v7

    // Vertex data for face 2
    1.0F, -1.0F, -1.0F, 0, 0, -1, 0.666F, 0.5F, 0.0F, // v8
    -1.0F, -1.0F, -1.0F, 0, 0, -1, 1.0F, 0.5F, 0.0F,  // v9
    1.0F, 1.0F, -1.0F, 0, 0, -1, 0.666F, 1.0F, 0.0F,  // v10
    -1.0F, 1.0F, -1.0F, 0, 0, -1, 1.0F, 1.0F, 0.0F,   // v11

    // Vertex data for face 3
    -1.0F, -1.0F, -1.0F, -1, 0, 0, 0.666F, 0.0F, 0.0F, // v12
    -1.0F, -1.0F, 1.0F, -1, 0, 0, 1.0F, 0.0F, 0.0F,    // v13
    -1.0F, 1.0F, -1.0F, -1, 0, 0, 0.666F, 0.5F, 0.0F,  // v14
    -1.0F, 1.0F, 1.0F, -1, 0, 0, 1.0F, 0.5F, 0.0F,     // v15

    // Vertex data for face 4
    -1.0F, -1.0F, -1.0F, 0, -1, 0, 0.333F, 0.0F, 0.0F, // v16
    1.0F, -1.0F, -1.0F, 0, -1, 0, 0.666F, 0.0F, 0.0F,  // v17
    -1.0F, -1.0F, 1.0F, 0, -1, 0, 0.333F, 0.5F, 0.0F,  // v18
    1.0F, -1.0F, 1.0F, 0, -1, 0, 0.666F, 0.5F, 0.0F,   // v19

    // Vertex data for face 5
    -1.0F, 1.0F, 1.0F, 0, 1, 0, 0.333F, 0.5F, 0.0F,  // v20
    1.0F, 1.0F, 1.0F, 0, 1, 0, 0.666F, 0.5F, 0.0F,   // v21
    -1.0F, 1.0F, -1.0F, 0, 1, 0, 0.333F, 1.0F, 0.0F, // v22
    1.0F, 1.0F, -1.0F, 0, 1, 0, 0.666F, 0.0F, 1.0F   // v23
};

constexpr std::array<GLuint, 34U> indices = {
    0,  1,  2,  3,  3,      // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
    4,  4,  5,  6,  7,  7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
    8,  8,  9,  10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
};

constexpr GLfloat VERTICAL_ANGLE = 60.0F;
constexpr GLfloat NEAR_PLANE = 0.1F;
constexpr GLfloat FAR_PLANE = 100.0F;

constexpr QVector4D CLEAR_COLOR(0.25F, 0.25F, 0.375F, 1.0F);

}

namespace Bazhenov {

void MainWindow::init() {
  // Configure OpenGL
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_MULTISAMPLE);

  glClearColor(CLEAR_COLOR.x(), CLEAR_COLOR.y(), CLEAR_COLOR.z(), CLEAR_COLOR.w());

  // Configure VBOs
  arrayBuf_.create();
  indexBuf_.create();

  arrayBuf_.bind();
  arrayBuf_.allocate(vertices.data(), static_cast<std::int32_t>(vertices.size() * sizeof(GLfloat)));

  indexBuf_.bind();
  indexBuf_.allocate(indices.data(), static_cast<std::int32_t>(indices.size() * sizeof(GLuint)));

  // Configure shaders
  program_ = std::make_unique<QOpenGLShaderProgram>(this);

  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vertex.glsl");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fragment.glsl");

  program_->link();

  // Configure attributes and uniforms
  posAttr_ = program_->attributeLocation("vertex_position");
  colAttr_ = program_->attributeLocation("vertex_color");
  matrixUniform_ = program_->uniformLocation("mvp_matrix");

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, VERTEX_POSITION_OFFSET, 3, STRIDE * sizeof(GLfloat));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT, VERTEX_COLOR_OFFSET, 3, STRIDE * sizeof(GLfloat));

  // Configure program engines
  inputController_ = std::make_shared<InputController>();
}

void MainWindow::render() {
  // Handle color selection
  inputController_->update();
  bool newColorSelected = inputController_->destructiveCheckNewColorSelected();

  if (newColorSelected) {
    QColor newColor = inputController_->getColor();
    for (auto i = 0U; i < vertices.size() / STRIDE; ++i) {
      vertices[STRIDE*i + VERTEX_COLOR_OFFSET]     = 0.5F * (vertices[STRIDE*i + VERTEX_COLOR_OFFSET]     + (i%2==0 ? newColor.redF() : 1.F - newColor.redF()));
      vertices[STRIDE*i + VERTEX_COLOR_OFFSET + 1] = 0.5F * (vertices[STRIDE*i + VERTEX_COLOR_OFFSET + 1] + (i%2==0 ? newColor.greenF() : 1.F - newColor.greenF()));
      vertices[STRIDE*i + VERTEX_COLOR_OFFSET + 2] = 0.5F * (vertices[STRIDE*i + VERTEX_COLOR_OFFSET + 2] + (i%2==0 ? newColor.blueF() : 1.F - newColor.blueF()));
    }

    arrayBuf_.release();
    arrayBuf_.bind();
    arrayBuf_.allocate(vertices.data(), static_cast<std::int32_t>(vertices.size() * sizeof(GLfloat)));
  }

  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Configure shaders, then launch rendering
  program_->bind();

  QMatrix4x4 mvp_matrix;
  mvp_matrix.perspective(VERTICAL_ANGLE, (GLfloat)width() / height(), NEAR_PLANE, FAR_PLANE);
  mvp_matrix.translate(0.0F, 0.0F, -5.0F);
  mvp_matrix.rotate(inputController_->getRotation());

  program_->setUniformValue(matrixUniform_, mvp_matrix);

  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), reinterpret_cast<void *>(VERTEX_POSITION_OFFSET * sizeof(GLfloat)));
  glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(GLfloat), reinterpret_cast<void *>(VERTEX_COLOR_OFFSET * sizeof(GLfloat)));

  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

  glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);

  program_->release();
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

}