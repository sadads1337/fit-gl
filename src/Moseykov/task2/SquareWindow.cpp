#include "SquareWindow.hpp"
#include <QScreen>
#include <QColorDialog>


namespace fgl {
SquareWindow::SquareWindow(QWidget *parent)
    :QOpenGLWidget(parent)
{   }



void SquareWindow::initializeGL() {
  initializeOpenGLFunctions();
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/square.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/square.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  Q_ASSERT(posAttr_ != -1);
  init_cube(1.5, 10);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  timer.start(30, this);
}

void SquareWindow::paintGL() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 view_matrix;
  view_matrix.setToIdentity();
  view_matrix.translate(0, 0, -4  );
  view_matrix.rotate(100.0 * frame_ / 59.0, rotationAxis);

  program_->bind();
  program_->setUniformValue("matrix", projection_matrix);
  program_->setUniformValue("view_matrix", view_matrix);
  program_->setUniformValue("morph_param", morph_param);

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(VertexData));
  program_->enableAttributeArray(posAttr_);
  glDrawElements(GL_LINES, indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
  program_->disableAttributeArray(posAttr_);

  program_->release();

  ++frame_;
}

void SquareWindow::resizeGL(const int w, const int h){
  const auto aspect = w / static_cast<double>(h);
  projection_matrix.setToIdentity();
  projection_matrix.perspective(60.0f, aspect, 0.01f, 100.0f);
}

void SquareWindow::change_morph_param(float value){
  morph_param = value/1000;
  update();
}

void SquareWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void SquareWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference
  // vector
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}

void SquareWindow::timerEvent(QTimerEvent * /*event*/){
  update();
}

void SquareWindow::init_cube(const float width, const int N) {

  auto width_div_2 = width / 2.0f;
  auto step = width / float(N - 1);
  QVector<VertexData> vertexes;
  for (auto z = -width_div_2; z <= width_div_2; z += width) {
    for (auto j = 0; j < N; j++) {
      for (auto i = 0; i < N; i++) {
        vertexes.append(VertexData(
            QVector3D(-width_div_2 + i*step, -width_div_2 + j * step, z)));
      }
    }
  }
  for (auto x = -width_div_2; x <= width_div_2; x += width) {
    for (auto k = 0; k < N; k++) {
      for (auto j = 0; j < N; j++) {
        vertexes.append(VertexData(
            QVector3D(x, -width_div_2 + j *step, width_div_2 - k*step)));
      }
    }
  }
  for (auto y = -width_div_2; y <= width_div_2; y += width) {
    for (auto i = 0; i < N; i++) {
      for (auto k = 0; k < N; k++) {
        vertexes.append(VertexData(
            QVector3D(-width_div_2 + i * step, y, width_div_2 - k*step)));
      }
    }
  }

  QVector<GLuint> indexes;
  for (int i = 0; i < 6 * N * N; i += N * N) {
    for (int j = 0; j < (N-1) * (N-1); j += N) {
      for (int k = 0; k < (N - 1); k++) {
        indexes.append(i + j + k + N);
        indexes.append(i + j + k + 0);
        indexes.append(i + j + k + N + 1);
        indexes.append(i + j + k + N + 1);
        indexes.append(i + j + k + 0);
        indexes.append(i + j + k + 1);
      }
    }
  }

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertexes.constData(),vertexes.size()*sizeof(VertexData));

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indexes.constData(),indexes.size()*sizeof(GLuint));

}
} // namespace fgl