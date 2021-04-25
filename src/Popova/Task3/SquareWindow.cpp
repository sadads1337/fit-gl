#include "SquareWindow.hpp"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QRgb>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>
#include <iostream>
namespace {

struct VertexData {
  QVector3D position;
  QVector3D color;
  QVector3D norm;
};

std::array<VertexData, 24u> vertices{{
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

    VertexData{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},

    VertexData{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},

    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

    VertexData{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

    VertexData{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},

    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
}};
std::array<GLushort, 36u> indices{
    {0,  3,  6,  6,  3,  9, 2,  7,  13, 13, 7,  23, 4,  1,  17, 17, 1,  14,
     19, 10, 16, 16, 10, 5, 18, 15, 21, 21, 15, 12, 11, 20, 8,  8,  20, 22}};

template <typename C, typename M>
inline ptrdiff_t memberOffset(M C::*member) noexcept {
  constexpr const char *null_ptr = nullptr;
  return reinterpret_cast<const char *>(
             &(static_cast<const C *>(nullptr)->*member)) -
         null_ptr;
}

} // namespace

namespace fgl {

void SquareWindow::init() {

  arrayBuf_.create();
  indexBuf_.create();

  arrayBuf_.bind();
  arrayBuf_.allocate(
      vertices.data(),
      static_cast<std::int32_t>(vertices.size() *
                                sizeof(decltype(vertices)::value_type)));

  indexBuf_.bind();
  indexBuf_.allocate(
      indices.data(),
      static_cast<std::int32_t>(indices.size() *
                                sizeof(decltype(indices)::value_type)));

  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/square.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/square.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  norm_ = program_->attributeLocation("norm");
  colAttr_ = program_->attributeLocation("colAttr");
  matrixUniform_ = program_->uniformLocation("matrix");
  matrixUniform2_ = program_->uniformLocation("model");

  program_->setAttributeBuffer(norm_, GL_FLOAT, memberOffset(&VertexData::norm),
                               3, sizeof(VertexData));
  program_->setAttributeBuffer(posAttr_, GL_FLOAT,
                               memberOffset(&VertexData::position), 3,
                               sizeof(VertexData));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT,
                               memberOffset(&VertexData::color), 3,
                               sizeof(VertexData));

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void SquareWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();
  for (int k = 0; k < 12; k++) {
    QMatrix4x4 matrix;
    QMatrix4x4 model;
    matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
    if (k < 4) {
      matrix.translate(k, 0, -5);
      model.translate(k, 0, -5);
    }
    if ((k >= 4) && (k < 8)) {
      matrix.translate(k - 4, 1, -5);
      model.translate(k - 4, 1, -5);
    }
    if ((k >= 8) && (k < 12)) {
      matrix.translate(k - 8, -1, -5);
      model.translate(k - 8, -1, -5);
    }

    matrix.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);
    model.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);
    matrix.scale(0.5, 0.5, 0.5);
    model.scale(0.5, 0.5, 0.5);
    program_->setUniformValue(matrixUniform_, matrix);
    program_->setUniformValue(matrixUniform2_, model);
    program_->setUniformValue("normal_matrix", model.normalMatrix());
    program_->setUniformValue("col", square_color);
    // Choose "0" to use Guro lighting model; "1" to use Phong lighting model
    program_->setUniformValue("lightModel", 0);

    program_->enableAttributeArray(norm_);
    program_->enableAttributeArray(posAttr_);
    program_->enableAttributeArray(colAttr_);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
    program_->disableAttributeArray(colAttr_);
    program_->disableAttributeArray(posAttr_);
    program_->disableAttributeArray(norm_);
  }

  program_->release();

  ++frame_;
}
void SquareWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    square_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                             color.blue() / 255.0, 1);
  }
}
void SquareWindow::mousePressEvent(QMouseEvent *e) {
  mousePressPosition = QVector2D(e->localPos());
}

void SquareWindow::mouseReleaseEvent(QMouseEvent *event) {
  const auto diff = QVector2D(event->localPos()) - mousePressPosition;
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}
} // namespace fgl