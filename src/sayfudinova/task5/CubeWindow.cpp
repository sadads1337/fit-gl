#include "CubeWindow.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>

namespace {
std::array<QVector3D, 9u> cubePosition{
    QVector3D(1.0f, 0.5f, -2.0f),   QVector3D(-0.2f, -0.1f, -1.2f),
    QVector3D(-0.8f, -0.6f, -1.6f), QVector3D(0.4f, -0.4f, -3.5f),
    QVector3D(-0.7f, 0.8f, -2.5f),  QVector3D(1.3f, -0.8f, -2.5f),
    QVector3D(0.7f, 1.0f, -2.5f),   QVector3D(0.8f, 0.2f, -4.5f),
    QVector3D(-1.5f, 1.2f, -2.5f)};

struct VertexData {
  QVector3D position;
  QVector3D norm;
};

std::array<VertexData, 24u> vertices{{
    VertexData{{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    VertexData{{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},

    VertexData{{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}},

    VertexData{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}},

    VertexData{{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}},

    VertexData{{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    VertexData{{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},

    VertexData{{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},

    VertexData{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},

    VertexData{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
}};

std::array<GLushort, 36u> indices{
    {0,  3,  6,  6,  3,  9, 2,  7,  13, 13, 7,  23, 4,  1,  17, 17, 1,  14,
     19, 10, 16, 16, 10, 5, 18, 15, 21, 21, 15, 12, 11, 20, 8,  8,  20, 22}};

} // namespace

namespace fgl {

void CubeWindow::init() {
  // Enable depth test and face culling
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Create VBO and IBO
  vbo_.create();
  ibo_.create();

  // Fill VBO
  vbo_.bind();
  vbo_.allocate(vertices.data(),
                static_cast<std::int32_t>(
                    vertices.size() * sizeof(decltype(vertices)::value_type)));

  // Fill IBO
  ibo_.bind();
  ibo_.allocate(indices.data(),
                static_cast<std::int32_t>(
                    indices.size() * sizeof(decltype(indices)::value_type)));

  // Configure shaders
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/quad.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/quad.fs");
  program_->link();

  // Configure attributes and uniforms
  posAttr_ = program_->attributeLocation("posAttr");
  norm_ = program_->attributeLocation("norm");
  matrixUniform_ = program_->uniformLocation("matrix");
  modelUniform_ = program_->uniformLocation("model");

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(VertexData));
  program_->setAttributeBuffer(norm_, GL_FLOAT, 3 * sizeof(float), 3,
                               sizeof(VertexData));
}

void CubeWindow::render() {
  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Bind shader
  program_->bind();

  for (int k = 0; k < 9; k++) {
    // Calculate MVP
    QMatrix4x4 matrix;
    QMatrix4x4 model;
    matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);

    matrix.translate(cubePosition[k]);
    model.translate(cubePosition[k]);

    matrix.rotate(10.0 * (k + 1) * frame_ / screen()->refreshRate(),
                  rotationAxis_);
    model.rotate(10.0 * (k + 1) * frame_ / screen()->refreshRate(),
                 rotationAxis_);
    matrix.scale(0.3f, 0.3f, 0.3f);
    model.scale(0.3f, 0.3f, 0.3f);

    //  matrix.translate(0, 0, -2);
    //  matrix.rotate(20.0 * frame_ / screen()->refreshRate(), rotationAxis_);
    //  model.translate(0, 0, -2);
    //  model.rotate(20.0 * frame_ / screen()->refreshRate(), rotationAxis_);
    //
    //  matrix.scale(0.8f, 0.8f, 0.8f);
    //  model.scale(0.8f, 0.8f, 0.8f);

    // Set attrs and unis
    program_->setUniformValue(matrixUniform_, matrix);
    program_->setUniformValue(modelUniform_, model);
    program_->setUniformValue("normal_matrix", model.normalMatrix());
    program_->setUniformValue("col", changeColor_);

    // "0" GOURAUD
    // "1" PHONG
    program_->setUniformValue("lightModel", 0);

    program_->enableAttributeArray(norm_);
    program_->enableAttributeArray(posAttr_);

    // Draw
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);

    program_->disableAttributeArray(posAttr_);
    program_->disableAttributeArray(norm_);
  }
  // Release all and increase counter
  program_->release();
  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    const auto color = QColorDialog::getColor();
    changeColor_ = QVector4D(color.red() / 255.0, color.green() / 255.0,
                             color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  mousePressPosition_ = QVector2D(event->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *event) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(event->localPos()) - mousePressPosition_;

  rotationAxis_ = QVector3D(diff.y(), diff.x(), 0.0f).normalized();
}
} // namespace fgl