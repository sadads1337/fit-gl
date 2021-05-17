#include "CubeWindow.hpp"
#include <QApplication>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_0_Core>
#include <QRgb>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>
#include<iostream>

namespace {

struct VertexData {
  QVector3D position;
  QVector3D color;
  QVector3D norm;
  QVector2D text_coord;
  QVector3D tangent;
  QVector3D bitangent;
};

std::array<VertexData, 24u> vertices{{
    VertexData{{0.5f, 0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, 1.0f},
               {1.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, 0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 1.0f, 0.0f},
               {1.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, 0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {1.0f, 0.0f, 0.0f},
               {1.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{-0.5f, 0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, 1.0f},
               {0.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, 0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 1.0f, 0.0f},
               {0.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, 0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {-1.0f, 0.0f, 0.0f},
               {1.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{0.5f, -0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, 1.0f},
               {1.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, -0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {1.0f, 0.0f, 0.0f},
               {1.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, -0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, -1.0f, 0.0f},
               {1.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{-0.5f, -0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, 1.0f},
               {0.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, -0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {-1.0f, 0.0f, 0.0f},
               {1.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, -0.5f, 0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, -1.0f, 0.0f},
               {0.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{0.5f, 0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, -1.0f},
               {1.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, 0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {1.0f, 0.0f, 0.0f},
               {0.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, 0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 1.0f, 0.0f},
               {1.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{-0.5f, 0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, -1.0f},
               {0.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, 0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {-1.0f, 0.0f, 0.0f},
               {0.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, 0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 1.0f, 0.0f},
               {0.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{-0.5f, -0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, -1.0f},
               {0.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, -0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {-1.0f, 0.0f, 0.0f},
               {0.0f, 1.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{-0.5f, -0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, -1.0f, 0.0f},
               {0.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},

    VertexData{{0.5f, -0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, 0.0f, -1.0f},
               {1.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, -0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {0.0f, -1.0f, 0.0f},
               {1.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    VertexData{{0.5f, -0.5f, -0.5f},
               {1.0f, 0.0f, 1.0f},
               {1.0f, 0.0f, 0.0f},
               {0.0f, 0.0f},
               {0.0f, 0.0f, 0.0f},
               {}},
    }
};

std::array<GLushort, 36u> indixes{
    {0,  3,  6,  6,  3,  9, 2,  7,  13, 13, 7,  23, 4,  1,  17, 17, 1,  14,
     19, 10, 16, 16, 10, 5, 18, 15, 21, 21, 15, 12, 11, 20, 8,  8,  20, 22}
};

template <typename C, typename M>
inline ptrdiff_t memberOffset(M C::*member) noexcept {
  constexpr const char *null_ptr = nullptr;
  return reinterpret_cast<const char *>(
             &(static_cast<const C *>(nullptr)->*member)) -
         null_ptr;
}

} // namespace

namespace fgl {


void CubeWindow::init() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  initTangentBitangent();

  vbo.create();
  ibo.create();

  vbo.bind();
  vbo.allocate(
      vertices.data(),
      static_cast<std::int32_t>(vertices.size() *
                                sizeof(decltype(vertices)::value_type)));

  ibo.bind();
  ibo.allocate(
      indixes.data(),
      static_cast<std::int32_t>(indixes.size() *
                                sizeof(decltype(indixes)::value_type)));

  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/cube.fs");
  program_->link();

  posAttr_ = program_->attributeLocation("posAttr");
  norm_ = program_->attributeLocation("norm");
  colAttr_ = program_->attributeLocation("colAttr");
  textCoord_ = program_->attributeLocation("a_texcoord");
  tangent_ = program_->attributeLocation("tangent");
  bitangent_ = program_->attributeLocation("bitangent");
  matrixUniform_ = program_->uniformLocation("matrix");
  matrixUniform2_ = program_->uniformLocation("model");

  program_->setAttributeBuffer(textCoord_, GL_FLOAT,
                               memberOffset(&VertexData::text_coord), 2,
                               sizeof(VertexData));
  program_->setAttributeBuffer(norm_, GL_FLOAT, memberOffset(&VertexData::norm),
                               3, sizeof(VertexData));
  program_->setAttributeBuffer(posAttr_, GL_FLOAT,
                               memberOffset(&VertexData::position), 3,
                               sizeof(VertexData));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT,
                               memberOffset(&VertexData::color), 3,
                               sizeof(VertexData));
  program_->setAttributeBuffer(tangent_, GL_FLOAT,
                               memberOffset(&VertexData::tangent), 3,
                               sizeof(VertexData));
  program_->setAttributeBuffer(bitangent_, GL_FLOAT,
                               memberOffset(&VertexData::bitangent), 3,
                               sizeof(VertexData));  
  initTextures();

}

void CubeWindow::render() {

  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();
  texture->bind(0);
  normal_map->bind(1);

  QMatrix4x4 matrix;
  QMatrix4x4 model;
  matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);
  matrix.scale(0.5f, 0.5f, 0.5f);

  model.translate(0, 0, -2);
  model.rotate(50.0 * frame_ / screen()->refreshRate(), rotationAxis);
  model.scale(0.5f, 0.5f, 0.5f);

  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue(matrixUniform2_, model);
  program_->setUniformValue("normal_matrix", model.normalMatrix());
  program_->setUniformValue("col", cube_color);
    

  program_->setUniformValue("lightModel", 1);
  program_->setUniformValue("texture", 0);
  program_->setUniformValue("normal_map", 1);
  program_->enableAttributeArray(norm_);
  program_->enableAttributeArray(textCoord_);
  program_->enableAttributeArray(posAttr_);
  program_->enableAttributeArray(colAttr_);
  program_->enableAttributeArray(tangent_);
  program_->enableAttributeArray(bitangent_);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);
  program_->disableAttributeArray(colAttr_);
  program_->disableAttributeArray(posAttr_);
  program_->disableAttributeArray(norm_);
  program_->disableAttributeArray(textCoord_);
  program_->disableAttributeArray(tangent_);
  program_->disableAttributeArray(bitangent_);


  program_->release();
  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    cube_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                           color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  mousePressPosition = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  const auto diff = QVector2D(event->localPos()) - mousePressPosition;
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}


void CubeWindow::initTextures() {
  texture = new QOpenGLTexture(QImage(":/textures/brickwall.jpg").mirrored());
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);

  normal_map = new QOpenGLTexture(QImage(":/textures/brickwall_normal.jpg").mirrored());
  normal_map->setMinificationFilter(QOpenGLTexture::Nearest);
  normal_map->setMagnificationFilter(QOpenGLTexture::Linear);
  normal_map->setWrapMode(QOpenGLTexture::Repeat);
}
void CubeWindow::initTangentBitangent() {
  QVector3D tangent, bitangent;
  for (auto i = 0; i < 12; i++) {
    auto j1 = indixes[i * 3];
    auto j2 = indixes[i * 3 + 1];
    auto j3 = indixes[i * 3 + 2];
    auto pos1 = vertices[j1].position;
    auto pos2 = vertices[j2].position;
    auto pos3 = vertices[j3].position;
    auto uv1 = vertices[j1].text_coord;
    auto uv2 = vertices[j2].text_coord;
    auto uv3 = vertices[j3].text_coord;

    auto delta1 = pos2 - pos1;
    auto delta2 = pos3 - pos1;
    auto deltaUV1 = uv2 - uv1;
    auto deltaUV2 = uv3 - uv1;
    float f =
        1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV2.x() * deltaUV1.y());
    tangent.setX(f * (deltaUV2.y() * delta1.x() - deltaUV1.y() * delta2.x()));
    tangent.setY(f * (deltaUV2.y() * delta1.y() - deltaUV1.y() * delta2.y()));
    tangent.setZ(f * (deltaUV2.y() * delta1.z() - deltaUV1.y() * delta2.z()));
    tangent.normalized();
    vertices[j1].tangent = tangent;
    vertices[j2].tangent = tangent;
    vertices[j3].tangent = tangent;
    bitangent.setX(f *
                   (-deltaUV2.x() * delta1.x() + deltaUV1.x() * delta2.x()));
    bitangent.setY(f *
                   (-deltaUV2.x() * delta1.y() + deltaUV1.x() * delta2.y()));
    bitangent.setZ(f *
                   (-deltaUV2.x() * delta1.z() + deltaUV1.x() * delta2.z()));
    bitangent.normalized();
    vertices[j1].bitangent = bitangent;
    vertices[j2].bitangent = bitangent;
    vertices[j3].bitangent = bitangent;
  }
}






} // namespace fgl