#include "GLWidget.hpp"
#include <QColorDialog>
#include <QMouseEvent>
#include <QScreen>
#include <array>
#include <iostream>
namespace {

} // namespace


void GLWidget::initializeGL()
{
  morphFactor = 0;
  aspect = 4.0/3.0;
  initializeOpenGLFunctions();
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/vertexShader.glsl");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/fragmentShader.glsl");
  program_->link();

  initCube(0.5, 3);

  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);

    // Enable Z-test    
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);


    FPS_timer.start(1000.0/FPS_COUNT, this);
    }



void GLWidget::paintGL() {

  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  VBO.bind();
  IBO.bind();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();

  QMatrix4x4 perspective_matrix;
  perspective_matrix.perspective(60.0f, aspect, 0.1f, 100.0f);
  perspective_matrix.translate(0, 0, -2);
  perspective_matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);
  program_->setUniformValue(matrixUniform_, perspective_matrix);

  program_->setUniformValue("col", square_color);
  program_->setUniformValue("morphFactor", morphFactor);

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3);
  glEnableVertexAttribArray(posAttr_);


 glDrawElements(GL_LINE_STRIP, GLsizei(indices.size()), GL_UNSIGNED_SHORT, nullptr);

  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}
void GLWidget::resizeGL(const int w, const int h) {

  aspect = w / static_cast<double>(h);
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *) {
  QColor color = QColorDialog::getColor();
  square_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                           color.blue() / 255.0, 1.0);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  lastPos = QVector2D(event->localPos());
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  const auto diff = QVector2D(event->localPos()) - lastPos;
  if (event->buttons() == Qt::LeftButton) {
    rotationAxis = QVector3D(diff.y(),diff.x(), 0.0);
  }

}
void GLWidget::timerEvent(QTimerEvent *) { update(); }

void GLWidget::initCube(GLfloat halfWidth, unsigned int N = 1) {


  // Add vertices
  Q_ASSERT(halfWidth >= 0);
  Q_ASSERT(N>= 1U);

  for (auto face = 0; face < 6; ++face) {

    const auto fixedPos = face % 3;
    const auto varPos1 = (face + 1) % 3;
    const auto varPos2 = (face + 2) % 3;

    for (auto y = 0U; y < N + 1; ++y) {
      for (auto x = 0U; x < N + 1; ++x) {
        auto position = QVector3D{0, 0, 0};
        
        if (face >=3) position[fixedPos] = halfWidth;
        else  position[fixedPos] = -1 * halfWidth  ;
        position[varPos1] = (x * 2.0F / N - 1.0F) * halfWidth;
        position[varPos2] = (y * 2.0F / N - 1.0F) * position[fixedPos];

        vertices.emplace_back(position);
      }
    }
    VBO.create();
    VBO.bind();
    VBO.allocate(vertices.data(), int(vertices.size() * sizeof(QVector3D)));


    // Add indices
    const auto faceOffset = face * (N + 1) * (N + 1);
    for (auto y = 0U; y < N; ++y) {
      const auto rowOffset = (N + 1) * y;
      indices.emplace_back(faceOffset + rowOffset);
      for (auto x = 0U; x < N + 1; ++x) {
        indices.emplace_back(faceOffset + rowOffset + x);
        indices.emplace_back(faceOffset + rowOffset + x + (N + 1));
      }
      indices.emplace_back(faceOffset + rowOffset + N + (N + 1));
    }
  }
  IBO.create();
  IBO.bind();
  IBO.allocate(indices.data(), int(indices.size() * sizeof(GLushort)));

}
void GLWidget::changeN(int N) {
  vertices.clear();
  indices.clear();
  initCube(0.5, N);
}
void GLWidget::changeFactor(int MF) {
  morphFactor = static_cast<double>(MF) / 100.0;
}