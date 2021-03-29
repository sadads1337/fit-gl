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
namespace {

struct VertexData {
  QVector3D position;
  QVector3D color;
  QVector3D norm;
};

std::array<VertexData, 24u> vertices{{
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,1.0f}},
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,1.0f,0.0f}},
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f,0.0f,0.0f}},

    VertexData{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,1.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,1.0f,0.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f,0.0f,0.0f}},

    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,1.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f,0.0f,0.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,-1.0f,0.0f}},

    VertexData{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,1.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f,0.0f,0.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,-1.0f,0.0f}},

    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,-1.0f}},
    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f,0.0f,0.0f}},
    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,1.0f,0.0f}},

    VertexData{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,-1.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f,0.0f,0.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,1.0f,0.0f}},

    VertexData{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,-1.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {-1.0f,0.0f,0.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,-1.0f,0.0f}},

    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,0.0f,-1.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f,-1.0f,0.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f,0.0f,0.0f}},
}
};
// std::array<GLushort, 14u> indices{{5, 4, 6, 7, 2, 4, 0, 5, 1, 6, 3, 2, 1, 0}};
std::array<GLushort, 36u> indices{{0, 3, 6, 6, 3, 9, 2, 7, 13, 13, 7, 23, 4, 1, 17, 17, 1, 14, 19, 10, 16, 16, 10, 5, 18, 15, 21, 21, 15, 12, 11, 20, 8, 8, 20, 22 }};
// std::array<QVector3D, 6u> norm{{
// {1.0f, 0.0f, 0.0f}, 
// {-1.0f, 0.0f, 0.0f}, 
// {0.0f, 1.0f, 0.0f}, 
// {0.0f, -1.0f, 0.0f}, 
// {0.0f, 0.0f, 1.0f}, 
// {0.0f, 0.0f, -1.0f}, 
// }};
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
  normalBuf_.create();

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
  matrixUniform2_ = program_->uniformLocation("matrix2");

  program_->setAttributeBuffer(posAttr_, GL_FLOAT,
                               memberOffset(&VertexData::norm), 3,
                               sizeof(VertexData::norm));

  program_->setAttributeBuffer(posAttr_, GL_FLOAT,
                               memberOffset(&VertexData::position), 3,
                               sizeof(VertexData::position));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT,
                               memberOffset(&VertexData::color), 3,
                               sizeof(VertexData::color));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void SquareWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();
  for (int k = 0; k<12; k++){
  QMatrix4x4 matrix;
  QMatrix4x4 matrix2;
   matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
  if (k<4) {
    matrix.translate(k, 0, -5);
   matrix2.translate(k, 0, -5);
  }
  if ((k>=4)&&(k<8)) {
    matrix.translate(k-4, 1, -5);
   matrix2.translate(k-4, 1, -5);
  }
  if ((k>=8)&&(k<12)) {
    matrix.translate(k-8, -1, -5);
   matrix2.translate(k-8, -1, -5);
  }
  
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);
  matrix.scale(0.5, 0.5, 0.5);
  matrix2.scale(0.5, 0.5, 0.5);
  program_->setUniformValue(matrixUniform_, matrix);
 program_->setUniformValue(matrixUniform2_, matrix2);
  program_->setUniformValue("col", square_color);
  glVertexAttribPointer(norm_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
  glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                        reinterpret_cast<char *>(sizeof(QVector3D)));

  glEnableVertexAttribArray(norm_);
  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);
  glDisableVertexAttribArray(norm_);

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