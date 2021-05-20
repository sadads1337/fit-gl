#include "QuadWindow.hpp"
#include <QScreen>
#include <array>
#include <QMouseEvent>
#include <QColorDialog>
namespace {

struct VertexData 
{
  QVector3D position;
  QVector3D color;
};

constexpr std::array<VertexData, 8u> vertices{
    // front dots
    VertexData{{0.5f, 0.5, 0.5f}, {1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    VertexData{{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}},
    // back dots
    VertexData{{0.5f, 0.5, -0.5f}, {1.0f, 0.0f, 0.0f}},
    VertexData{{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    VertexData{{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
    VertexData{{-0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}},
};
constexpr std::array<GLushort, 26u> indices{0, 1, 2, 3,  // front face
                                  3, 7, 2, 6, // bottom face
                                  6, 7, 4, 5, // back face
                                  5, 1, 4, 0,  // upper face
                                  0, 2, 4, 6, 6,// right face
                                  7, 7, 3 , 5, 1 // left face
};
} // namespace


void MainWindow::init()
{
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/vertexShader.glsl");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/fragmentShader.glsl");
  program_->link();



  VBO.create();
  IBO.create();

  VBO.bind();
  IBO.bind();
  
  VBO.allocate(vertices.data(), static_cast<int>(vertices.size() * sizeof(VertexData)));
  IBO.allocate(indices.data(), static_cast<int>(indices.size() * sizeof(GLushort)));

  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);

    // Enable Z-test    
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    }



void MainWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  VBO.bind();
  IBO.bind();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  program_->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);
  program_->setUniformValue(matrixUniform_, matrix);

  program_->setUniformValue("add_col", additional_color);

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(VertexData));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT, sizeof(QVector3D), 3, sizeof(VertexData));
  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);


 glDrawElements(GL_TRIANGLE_STRIP, GLsizei(indices.size()), GL_UNSIGNED_SHORT, nullptr);

  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *) {
  const auto color = QColorDialog::getColor();
  additional_color = QVector4D(color.red() / 255.0, color.green() / 255.0,
                           color.blue() / 255.0, 1.0);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  // Save mouse press position
  lastPos = QVector2D(event->localPos());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  const auto diff = QVector2D(event->localPos()) - lastPos;
  if (event->buttons() == Qt::LeftButton) {
    rotationAxis = QVector3D(diff.y(),diff.x(), 0.0);
  }
}

