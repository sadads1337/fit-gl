#include "MainWindow.h"
#include <QOpenGLContext>
#include <QImage>
#include <vector>
#include <QtMath>
#include <stdexcept>

#define refreshRate 59


namespace fgl {

MainWindow::MainWindow(QWidget *parent)
    :QOpenGLWidget(parent)
{
  morph_param = 1;
}

MainWindow::~MainWindow() = default;

void MainWindow::initializeGL() {

  initializeOpenGLFunctions();
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/vertex_shader.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/fragment_shader.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  Q_ASSERT(posAttr_ != -1);

  normAttr_ = program_->attributeLocation("normAttr");
  Q_ASSERT(normAttr_ != -1);

  textureAttr_ = program_->attributeLocation("textureAttr");
  Q_ASSERT(textureAttr_ != -1);

  initCube(2.0f,10);

  img = QImage(":/Texture/Texture_1");
  Q_ASSERT(img.isNull());

  glClearColor(0.0f,0.3f,0.0f, 0.8f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  timer.start(30, this);
}

void MainWindow::resizeGL(const int w,const  int h){
  const auto aspect = w / static_cast<double> (h);
  projection_matrix.setToIdentity();
  projection_matrix.perspective(60.0f, aspect, 0.1f, 100.0f);
}

void MainWindow:: paintGL() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();


    QMatrix4x4 view_matrix;
    QMatrix4x4 model_matrix;
    view_matrix.translate(0.0, 0.0, -4.0);
    model_matrix.translate(0.0, 0.0, -4.0);

    //  QMatrix4x4 view_matrix;
    view_matrix.setToIdentity();
    view_matrix.rotate(100.0 * frame_ / refreshRate, rotationAxis);
    model_matrix.rotate(100.0 * frame_ / refreshRate, rotationAxis);
    view_matrix.scale(0.7f, 0.7f, 0.7f);
    model_matrix.scale(0.7f, 0.7f, 0.7f);


    program_->setUniformValue("u_projection_matrix", projection_matrix);
    program_->setUniformValue("u_view_matrix", view_matrix);
    program_->setUniformValue("u_model_matrix", model_matrix);
    program_->setUniformValue("objectColor", square_color);
    program_->setUniformValue("u_morph_param", morph_param);
    program_->setUniformValue("lightPos", QVector3D(0.0, 0.0, 0.0));
    program_->setUniformValue("normal_matrix", model_matrix.normalMatrix());
    program_->setUniformValue("viewPos", QVector3D(-1, 0.0, 0.0));
    program_->setUniformValue("light_model", 1); // 0 -Gourand, 1 - Phong

    vertexBuffer.bind();

    program_->enableAttributeArray(posAttr_);
    program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3,
                                 sizeof(VertexData));


    program_->enableAttributeArray(normAttr_);
    program_->setAttributeBuffer(normAttr_, GL_FLOAT, sizeof(QVector3D) , 3, sizeof(VertexData));

    program_->enableAttributeArray(textureAttr_);
    program_->setAttributeBuffer(textureAttr_, GL_FLOAT, 2*sizeof(QVector3D) , 2, sizeof(VertexData));


    indexBuffer.bind();

    //Work with textures
    GLuint texture;
    context()->functions()->glGenTextures(1, &texture);
    context()->functions()->glBindTexture(GL_TEXTURE_2D, texture);
    context()->functions()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.width(), img.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.bits());
    context()->functions()->glGenerateMipmap(GL_TEXTURE_2D);


    context()->functions()->glDrawElements(GL_LINES, indexBuffer.size(),
                                           GL_UNSIGNED_INT, nullptr);

    program_->disableAttributeArray(posAttr_);
    program_->disableAttributeArray(normAttr_);
    program_->disableAttributeArray(textureAttr_);


    program_->release();

    ++frame_;
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
  QWidget::mousePressEvent(e);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference
  // vector
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  update();
}

void MainWindow::timerEvent(QTimerEvent *){
  update();
}


void MainWindow::initCube(const float width, const int N) {
  if(N < 2) {
    throw std::invalid_argument("The number of partitions must be greater than 1");
  }
  auto width_div_2 = width / 2.0f;
  auto step = width / float(N - 1);

  std::vector<VertexData> vertexes;
  vertexes.reserve(6 * pow(N, 2));
  for (auto z = -width_div_2; z <= width_div_2; z += width) {
    for (auto j = 0; j < N; j++) {
      for (auto i = 0; i < N; i++) {
        vertexes.emplace_back( VertexData(QVector3D( -width_div_2 + i*step, -width_div_2 + j * step, z), QVector3D(0.0,0.0, z/width_div_2), QVector2D(-width_div_2 + i*step, -width_div_2 + j * step)));
      }
    }
  }
  for (auto x = -width_div_2; x <= width_div_2; x += width) {
    for (auto k = 0; k < N; k++) {
      for (auto j = 0; j < N; j++) {
        vertexes.emplace_back(VertexData(
            QVector3D( x, -width_div_2 + j *step, + width_div_2 - k*step), QVector3D(x/width_div_2, 0.0, 0.0), QVector2D(-width_div_2 + j *step, + width_div_2 - k*step)));
      }
    }
  }
  for (auto y = -width_div_2; y <= width_div_2; y += width) {
    for (auto i = 0; i < N; i++) {
      for (auto k = 0; k < N; k++) {
        vertexes.emplace_back(VertexData(
            QVector3D(-width_div_2 + i * step, y, width_div_2 - k*step), QVector3D(0.0,y/width_div_2, 0.0), QVector2D(-width_div_2 + i * step,width_div_2 - k*step)));
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

void MainWindow::set_morph_param(float value){
  morph_param = value/100.0f;
  update();
}

void MainWindow::set_color(QColor color){

  square_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                           color.blue() / 255.0, 1);
  update();
}

} // namespace fgl