#include "SquareWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>
#include <QOpenGLBuffer>
#include <QColorDialog>
#include <QMouseEvent>
#include <QRgb>
namespace {

  struct VertexData
  {
    QVector3D position;
    QVector3D texCoord;
  };

std::array<VertexData, 8u> vertices{
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, 0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, 0.5f,  -0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, 0.5f,  -0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, -0.5f,  -0.5f}, {1.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, -0.5f,  -0.5f}, {1.0f, 0.0f, 1.0f}},
};
std::array<GLushort, 14u> indices{
    5,4,6,7,2,4,0,5,1,6,3,2,1,0
};

template <typename C, typename M>
inline ptrdiff_t memberOffset(M C::* member) noexcept {
  constexpr const std::byte *null_ptr = nullptr;
  return reinterpret_cast<const std::byte *>(
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
  indexBuf_.allocate(indices.data(), static_cast<std::int32_t>(indices.size() * sizeof(decltype(indices)::value_type)));

  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/square.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/square.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  colAttr_ = program_->attributeLocation("colAttr");
  matrixUniform_ = program_->uniformLocation("matrix");

  program_->setAttributeBuffer(posAttr_, GL_FLOAT,
                               memberOffset(&VertexData::position), 3,
                               sizeof(VertexData::position));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT,
                               memberOffset(&VertexData::texCoord), 3,
                               sizeof(VertexData::texCoord));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

}

void SquareWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();
  QMatrix4x4 matrix;
  matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);
  matrix.scale(0.5, 0.5, 0.5);
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", square_color );

  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
  glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<char *>(sizeof(QVector3D) ));

  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

  glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_SHORT, nullptr);
  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}
void SquareWindow::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Space){
      const auto color = QColorDialog::getColor();
      square_color = QVector4D(color.red() / 255.0, color.green()/255.0, color.blue()/255.0, 1);
    }
}
void SquareWindow::mousePressEvent(QMouseEvent *e){
        mousePressPosition = QVector2D(e->localPos());
    }

void SquareWindow::mouseReleaseEvent(QMouseEvent *event){
        const auto diff = QVector2D(event->localPos()) - mousePressPosition;
        rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
    }
} 