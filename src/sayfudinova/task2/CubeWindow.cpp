#include "CubeWindow.h"

#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QScreen>

struct VertexData{
  VertexData(){ }
  VertexData(QVector3D p) :
      position(p){ }
  QVector3D position;
};

void CubeWindow::initCube(float width, int N) {
  float halfWidth = width/2;
  float step = width/float(N-1);

  QVector<VertexData> vertices;
  for (auto z = -halfWidth; z <= halfWidth; z += width) {
    for (auto j = 0; j < N; j++) {
      for (auto i = 0; i < N; i++) {
        vertices.append(VertexData(
            QVector3D(-halfWidth + i*step, -halfWidth + j * step, z)));
      }
    }
  }
  for (auto x = -halfWidth; x <= halfWidth; x += width) {
    for (auto k = 0; k < N; k++) {
      for (auto j = 0; j < N; j++) {
        vertices.append(VertexData(
            QVector3D(x, -halfWidth + j *step, halfWidth - k*step)));
      }
    }
  }
  for (auto y = -halfWidth; y <= halfWidth; y += width) {
    for (auto i = 0; i < N; i++) {
      for (auto k = 0; k < N; k++) {
        vertices.append(VertexData(
            QVector3D(-halfWidth + i * step, y, halfWidth - k*step)));
      }
    }
  }

  QVector<GLuint> indices;
  for (int i = 0; i < 6 * N * N; i += N * N) {
    for (int j = 0; j < (N-1) * (N-1); j += N) {
      for (int k = 0; k < (N - 1); k++) {
        indices.append(i + j + k + N);
        indices.append(i + j + k + 0);
        indices.append(i + j + k + N + 1);
        indices.append(i + j + k + N + 1);
        indices.append(i + j + k + 0);
        indices.append(i + j + k + 1);
      }
    }
  }

  vbo.create();
  vbo.bind();
  vbo.allocate(vertices.constData(),vertices.size()*sizeof(VertexData));

  ibo.create();
  ibo.bind();
  ibo.allocate(indices.constData(),indices.size()*sizeof(GLuint));

}

void CubeWindow::init() {
  // Enable depth test and face culling
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // Clear all buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  start = std::chrono::system_clock::now();

  initCube(2.f, 15);

  // Configure shaders
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/quad.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/quad.fs");
  program_->link();

  // Configure attributes and uniforms
  posAttr_ = program_->attributeLocation("posAttr");
  matrixUniform_ = program_->uniformLocation("matrix");

}

void CubeWindow::render() {
  auto end = std::chrono::system_clock::now();
  time_ = end - start;

  // Configure viewport
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // Clear buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Calculate MVP
  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);
  matrix.scale(0.6, 0.6, 0.6);

  // Bind shader and set attrs and unis
  program_->bind();
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue("col", changeColor);
  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(VertexData));
  program_->enableAttributeArray(posAttr_);

  program_->setUniformValue("time", time_.count());

  glDrawElements(GL_LINES, ibo.size(), GL_UNSIGNED_INT, nullptr);

  // Release all and increase counter
  program_->disableAttributeArray(posAttr_);
  program_->release();
  ++frame_;
}

void CubeWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    QColor color = QColorDialog::getColor();
    changeColor = QVector4D(color.red() / 255.0, color.green() / 255.0,
                            color.blue() / 255.0, 1);
  }
}

void CubeWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}
