#include "CubeWindow.hpp"

#include <QOpenGLFunctions>
#include <QScreen>

#include <array>

namespace {

   float positions[] = {
           -0.5f, -0.5f,  0.5f, //0
            0.5f, -0.5f,  0.5f, //1
           -0.5f,  0.5f,  0.5f, //2
            0.5f,  0.5f,  0.5f, //3
            0.5f, -0.5f, -0.5f, //4
            0.5f,  0.5f, -0.5f, //5
           -0.5f, -0.5f, -0.5f, //6
           -0.5f,  0.5f, -0.5f, //7
   };

   unsigned int indices[] = {
           0, 1, 2, 3, 3,    //front
           1, 1, 4, 3, 5, 5, //right
           4, 4, 6, 5, 7, 7, //back
           6, 6, 0, 7, 2, 2, //left
           6, 6, 4, 0, 1, 1, //bottom
           2, 2, 3, 7, 5     //top
   };

} // namespace

namespace fgl {

void CubeWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);

  //Compiles source as a shader of the specified type and adds it to this 
  //shader program. Returns true if compilation was successful, false otherwise. 
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/cube.fs");
  
  //Links together the shaders that were added to this program with addShader()
  program_->link();

  //Returns the location of the attribute
  posAttr_ = program_->attributeLocation("posAttr");
  assert(posAttr_ != -1);

  matrixUniform_ = program_->uniformLocation("matrix");
  assert(matrixUniform_ != -1);
  colorUniform_ = program_->uniformLocation("color");
  assert(colorUniform_ != -1);

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, 8*3*sizeof(float), positions, GL_STATIC_DRAW);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34*sizeof(unsigned int), indices, GL_STATIC_DRAW);

  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}

void CubeWindow::render() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Returns the ratio between physical pixels and device-independent pixels for the window.
  //This value is dependent on the screen the window
  //From QScreen
  const auto retinaScale = devicePixelRatio();

  //width, height from QScreen, in pixels
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  //Binds this shader program to the active QOpenGLContext and makes it the current shader program. 
  //Any previously bound shader program is released.
  program_->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

  //Sets the uniform variable called name in the current to a 4x4 matrix value.
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue(colorUniform_, color);

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);

  //Enable or disable a generic vertex attribute array
  glEnableVertexAttribArray(posAttr_);

  //render primitives from array data
  glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, nullptr);

  glDisableVertexAttribArray(posAttr_);


  //Releases the active shader program from the current QOpenGLContext.
  program_->release();

  ++frame_;
}

///// CHANGE ROTATION AXIS

void CubeWindow::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference vector
    rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}

///// CHANGE COLOR

void CubeWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Space)
    {
        QColor chosen_color = QColorDialog::getColor();
        color = QVector4D(chosen_color.red() / 255.0, chosen_color.green() / 255.0,
                                 chosen_color.blue() / 255.0, 0.2);
    }
}

} // namespace fgl