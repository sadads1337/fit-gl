#include "TriangleWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <array>
#include <cassert>

namespace {

constexpr std::array<GLfloat, 6u> gVertices = {0.0f,  0.707f, -0.5f,
                                               -0.5f, 0.5f,   -0.5f};
constexpr std::array<GLfloat, 9u> gColors = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                             0.0f, 0.0f, 0.0f, 1.0f};

} // namespace

namespace fgl {

void TriangleWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/triangle.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/triangle.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);
  colAttr_ = program_->attributeLocation("colAttr");
  assert(colAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);
}

void TriangleWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT);

  program_->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), 0, 1, 0);

  program_->setUniformValue(matrixUniform_, matrix);

  glVertexAttribPointer(posAttr_, static_cast<GLint>(gVertices.size() / 3u),
                        GL_FLOAT, GL_FALSE, 0, gVertices.data());
  glVertexAttribPointer(colAttr_, static_cast<GLint>(gColors.size() / 3u),
                        GL_FLOAT, GL_FALSE, 0, gColors.data());

  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}

} // namespace fgl