#include "SquareWindow.hpp"
#include <QScreen>
#include <QColorDialog>
#include <QtMath>

namespace fgl {
SquareWindow::SquareWindow(QWidget *parent)
    :QOpenGLWidget(parent)
{  }



void SquareWindow::initializeGL() {
  initializeOpenGLFunctions();
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/phong.vs"); //phong.vs - for Phong; guro.vs - for Guro
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/phong.fs"); //phong.fs - for Phong; guro.fs - for Guro
  program_->link();


  posAttr_ = program_->attributeLocation("posAttr");
  normAttr_ = program_->attributeLocation("normAttr");
  Q_ASSERT(posAttr_ != -1);


  init_cube(1.5f, 10);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  timer.start(30, this);
}

void SquareWindow::paintGL() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 view_matrix;
  for(int k=0;k<3;k++) {
    for (int i = 0; i < 3; i++) {
      view_matrix.setToIdentity();
      view_matrix.translate(-2.5 + k * 2.5, -2.5 + i * 2.5, -8);
      view_matrix.rotate(100.0 * frame_ / 59.0, rotationAxis);
      program_->bind();
      program_->setUniformValue("projection_matrix", projection_matrix);
      program_->setUniformValue("model", view_matrix);
      program_->setUniformValue("view_matrix", view_matrix);
      program_->setUniformValue("morph_param", morph_param);
      program_->setUniformValue("norm_matrix", view_matrix.normalMatrix());
      program_->setUniformValue("viewPos", QVector3D(0.0, 0.0, 0));
      program_->setUniformValue("lightPos", QVector3D(3.0,1.0,-1.0));
      program_->setUniformValue("type_of_light_model", 2);



      program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3,
                                   sizeof(VertexData));
      program_->enableAttributeArray(posAttr_);

      program_->setAttributeBuffer(normAttr_, GL_FLOAT, sizeof(QVector3D) , 3, sizeof(VertexData));
      program_->enableAttributeArray(normAttr_);
      glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, nullptr);
      program_->disableAttributeArray(posAttr_);
    }
  }


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

void SquareWindow::change_type_of_light_model(float value){
    type_of_light_model = value;
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

    std::vector<VertexData> vertexes;
    vertexes.reserve(6 * pow(N, 2));
    for (auto z = -width_div_2; z <= width_div_2; z += width) {
        for (auto j = 0; j < N; j++) {
            for (auto i = 0; i < N; i++) {
                vertexes.emplace_back( VertexData(QVector3D( -z + i*step*z/width_div_2, -width_div_2 + j * step, z), QVector3D(0.0,0.0, z/width_div_2)));
            }
        }
    }
    for (auto x = -width_div_2; x <= width_div_2; x += width) {
        for (auto k = 0; k < N; k++) {
            for (auto j = 0; j < N; j++) {
                vertexes.emplace_back(VertexData(
                        QVector3D( x, -width_div_2 + j *step, -x + x*k*step/width_div_2), QVector3D(x/width_div_2, 0.0, 0.0)));
            }
        }
    }
    for (auto y = -width_div_2; y <= width_div_2; y += width) {
        for (auto i = 0; i < N; i++) {
            for (auto k = 0; k < N; k++) {
                vertexes.emplace_back(VertexData(
                        QVector3D(-width_div_2 + i * step, y, -y + y*k*step/width_div_2), QVector3D(0.0,y/width_div_2, 0.0)));
            }
        }
    }

    std::vector<GLuint> indexes;
    int vertex_count = 36 * pow (N-1, 2);
    indexes.reserve(vertex_count);
    for (int i = 0; i < 6 * N * N; i += N * N) {
        for (int j = 0; j < (N-1) * (N-1); j += N) {
            for (int k = 0; k < (N-1); k++) {
                indexes.emplace_back(i + j + k + N);
                indexes.emplace_back(i + j + k + 0);
                indexes.emplace_back(i + j + k + N + 1 );
                indexes.emplace_back(i + j + k + N + 1 );
                indexes.emplace_back(i + j + k + 0);
                indexes.emplace_back(i + j + k + 1);
            }
        }
    }

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vertexes.data(),static_cast <int>(vertexes.size()*sizeof(VertexData)));

    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indexes.data(),static_cast<int>(indexes.size()*sizeof(GLuint)));
}
} // namespace fgl