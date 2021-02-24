#include "TriangleWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <QMouseEvent>

#include <array>
#include <cassert>

namespace {

struct VertexData
{
  QVector3D position;
  QVector3D color;
};

VertexData gvertices[] = {

    {QVector3D(-0.5f,  -0.5f, 0.5f), QVector3D(2.0f, 0.0f, 0.0f)},  // v0
    {QVector3D( 0.5f, -0.5f, 0.5f), QVector3D(0.0f, 2.0f, 0.0f)}, // v1
    {QVector3D(-0.5f,  0.5f,  0.5f), QVector3D(0.0f, 0.0f, 2.0f)},  // v2
    {QVector3D( 0.5f, 0.5f, 0.5f), QVector3D(2.0f, 0.0f, 1.0f)}, // v3
    {QVector3D( 0.5f,   -0.5f, -0.5f), QVector3D(0.0f, 2.0f, 1.0f)},  // v4
    {QVector3D( 0.5f, 0.5f, -0.5f), QVector3D(0.0f, 1.0f, 2.0f)}, // v5
    {QVector3D( -0.5f,  -0.5f, -0.5f), QVector3D(2.0f, 0.0f, 1.0f)},// v6
    {QVector3D( -0.5f,   0.5f, -0.5f), QVector3D(1.0f, 2.0f, 0.0f)} // v7

};

constexpr std::array<GLuint ,34u> v_indicies = {
    0,  1,  2,  3,  3,
    1,  1,  4,  3,  5,  5,
    4,  4,  6, 5, 7, 7,
    6, 6, 0, 7, 2, 2,
    6, 6, 4, 0, 1, 1,
    2, 2, 3, 7, 5
};


} // namespace

namespace fgl {

void TriangleWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/triangle.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/triangle.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);
  colAttr_ = program_->attributeLocation("colAttr");
  assert(colAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

}

void TriangleWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT);

  program_->bind();

  //rotation
  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

  program_->setUniformValue(matrixUniform_, matrix);

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(VertexData), gvertices, GL_STATIC_DRAW);


  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
  glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<char *>(sizeof(QVector3D) ));

  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

  unsigned int v_ibo;
  glGenBuffers(1, &v_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v_ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(unsigned int), v_indicies.data(), GL_STATIC_DRAW);

  glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, nullptr);
  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}

void TriangleWindow::mousePressEvent(QMouseEvent *e)
{
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void TriangleWindow::mouseReleaseEvent(QMouseEvent *e)
{
  // Mouse release position - mouse press position
  QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;
// Mouse release position - mouse press position


  // Rotation axis is perpendicular to the mouse position difference
  // vector
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

  // Accelerate angular speed relative to the length of the mouse sweep
  qreal acc = diff.length() / 100.0;

  // Calculate new rotation axis as weighted sum
  rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

  // Increase angular speed
  angularSpeed += acc;
  // Rotation axis is perpendicular to the mouse position difference
  // vector
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}
//void TriangleWindow::timerEvent(QTimerEvent *)
//{
//  // Decrease angular speed (friction)
//  angularSpeed *= 0.99;
//
//  // Stop rotation when speed goes below threshold
//  if (angularSpeed < 0.01) {
//    angularSpeed = 0.0;
//  } else {
//    // Update rotation
//    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
//
//    // Request an update
//    update();
//  }
TriangleWindow::~TriangleWindow(){
  program_->removeAllShaders();
}

} // namespace fgl