#include "TriangleWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>
#include <QVector2D>
#include <QVector3D>
#include <array>
#include <QOpenGLBuffer>


namespace {

  struct VertexData
{
    QVector3D position;
    QVector3D texCoord;
};

VertexData vertices[] = {
   {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f, 0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.33f, 0.0f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f, 0.5f, 0.0f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.33f, 0.5f, 0.0f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D( 0.0f, 0.5f, 0.0f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.33f, 0.5f, 0.0f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.0f, 1.0f, 0.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.33f, 1.0f, 0.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.66f, 0.5f, 0.0f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(1.0f, 0.5f, 0.0f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.66f, 1.0f, 0.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(1.0f, 1.0f, 0.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.66f, 0.0f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(1.0f, 0.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.66f, 0.5f, 0.0f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(1.0f, 0.5f, 0.0f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.33f, 0.0f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.66f, 0.0f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.33f, 0.5f, 0.0f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.66f, 0.5f, 0.0f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.33f, 0.5f, 0.0f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.66f, 0.5f, 0.0f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.33f, 1.0f, 0.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.66f, 1.0f, 0.0f)}};  // v23
      //   {QVector3D(1.0f, 1.0f,  1.0f)},
      //  {QVector3D(-1.0f, 1.0f,  1.0f)},
      //   {QVector3D(1.0f, 1.0f,  -1.0f)},
      //  {QVector3D(-1.0f, 1.0f,  -1.0f)},
      //  {QVector3D(1.0f, -1.0f,  1.0f)},
      //   {QVector3D(-1.0f, -1.0f,  1.0f)},
      //   {QVector3D(-1.0f, -1.0f,  -1.0f)},
      //   {QVector3D(1.0f, -1.0f,  -1.0f)},
      //   };
GLushort indices[] = {
   0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23   
  // 3,2,6,7,4,2,0,3,1,6,5,4,1,0
  };

 } // namespace
//gldraw elements учитывает IBO
//.CREATE VBO IBO 
//.bind
//.allocate укаатель на массив vbo ibo

//вначале для vbo потом для ibo это все выполняем

namespace fgl {

void TriangleWindow::init() {

  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
  // Generate 2 VBOs
  arrayBuf.create();
  indexBuf.create();


// Transfer vertex data to VBO 0
  arrayBuf.bind();
  arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
  indexBuf.bind();
  indexBuf.allocate(indices, 34 * sizeof(GLushort));

  program_ = std::make_unique<QOpenGLShaderProgram>(this);
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/triangle.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/triangle.fs");
  program_->link();
  posAttr_ = program_->attributeLocation("posAttr");
  // assert(posAttr_ != -1);
  colAttr_ = program_->attributeLocation("colAttr");
  // assert(colAttr_ != -1);
  matrixUniform_ = program_->uniformLocation("matrix");
  // assert(matrixUniform_ != -1);

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
  program_->setAttributeBuffer(colAttr_, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
  // gl draw elements
}

void TriangleWindow::render() {
  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT);

  program_->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), 0, 1, 0);

  program_->setUniformValue(matrixUniform_, matrix);

    glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
    glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<char *>(sizeof(QVector3D) ));
  // glVertexAttribPointer(posAttr_, static_cast<GLint>(gVertices.size() / 3u),
  //                       GL_FLOAT, GL_FALSE);
  // glVertexAttribPointer(colAttr_, static_cast<GLint>(gColors.size() / 3u),
  //                       GL_FLOAT, GL_FALSE, 0, gColors.data());

  glEnableVertexAttribArray(posAttr_);
  glEnableVertexAttribArray(colAttr_);

 // Draw cube geometry using indices from VBO 1
  glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);

  glDisableVertexAttribArray(colAttr_);
  glDisableVertexAttribArray(posAttr_);

  program_->release();

  ++frame_;
}

} // namespace fgl