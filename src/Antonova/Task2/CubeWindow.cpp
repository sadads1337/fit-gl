#include "CubeWindow.hpp"
#include <QScreen>
#include <QtMath>
#include <vector>
#include <iostream>

namespace fgl {

void CubeWindow::makeCube(const float side_size, const int n_points) {

    auto side_half = side_size / 2.0f;
    auto step = side_size / float(n_points - 1);

    std::vector<QVector3D> vertices;
    vertices.reserve(6 * pow(n_points, 2));

    // bottom and top
    for (auto z = -side_half; z <= side_half; z += side_size) {
        for (auto j = 0; j < n_points; j++) {
            for (auto i = 0; i < n_points; i++) {
                vertices.emplace_back(QVector3D(-side_half + i * step, -side_half + j * step, z));
            }
        }
    }

    // left and right
    for (auto x = -side_half; x <= side_half; x += side_size) {
        for (auto k = 0; k < n_points; k++) {
            for (auto j = 0; j < n_points; j++) {
                vertices.emplace_back(QVector3D(x, -side_half + j * step, side_half - k * step));
            }
        }
    }

    // back and front
    for (auto y = -side_half; y <= side_half; y += side_size) {
        for (auto i = 0; i < n_points; i++) {
            for (auto k = 0; k < n_points; k++) {
                vertices.emplace_back(QVector3D(-side_half + i * step, y, side_half - k * step));
            }
        }
    }

    std::vector<GLuint> indices;
    indices.reserve(36 * pow(n_points - 1, 2));
    for (int i = 0; i < 6 * pow(n_points, 2); i += n_points * n_points) {
        for (int j = 0; j < (n_points - 1) * (n_points - 1); j += n_points) {
            for (int k = 0; k < (n_points - 1); k++) {
                indices.emplace_back(i + j + k + n_points);
                indices.emplace_back(i + j + k + 0);
                indices.emplace_back(i + j + k + n_points);
                indices.emplace_back(i + j + k + n_points + 1);
                indices.emplace_back(i + j + k + 0);
                indices.emplace_back(i + j + k + 1);
            }
        }
    }

    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vertices.data(),
                          static_cast<int>(vertices.size() * sizeof(QVector3D)));

    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indices.data(),
                         static_cast<int>(indices.size() * sizeof(GLuint)));
}

void CubeWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);

  // Compiles source as a shader of the specified type and adds it to this
  // shader program. Returns true if compilation was successful, false otherwise.
  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/cube.fs");

  // Links together the shaders that were added to this program with addShader()
  program_->link();

  // Returns the location of the attribute
  posAttr_ = program_->attributeLocation("posAttr");
  Q_ASSERT(posAttr_ != -1);

  // uniforms
  matrixUniform_ = program_->uniformLocation("matrix");
  Q_ASSERT(matrixUniform_ != -1);
  colorUniform_ = program_->uniformLocation("color");
  Q_ASSERT(colorUniform_ != -1);
  morphUniform_ = program_->uniformLocation("morph");
  Q_ASSERT(morphUniform_ != -1);


  makeCube(1.0f, 10);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  timer.start(5, this);
}

void CubeWindow::render() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Returns the ratio between physical pixels and device-independent pixels for the window.
  // This value is dependent on the screen the window. From QScreen
  const auto retinaScale = devicePixelRatio();
  // width, height from QScreen, in pixels
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  // Binds this shader program to the active QOpenGLContext and makes it the
  // current shader program. Any previously bound shader program is released.
  program_->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -3);
  matrix.rotate(60.0 * frame_ / screen()->refreshRate(), rotationAxis);

  // Sets the uniform variable called name in the current to a 4x4 matrix value.
  program_->setUniformValue(matrixUniform_, matrix);
  program_->setUniformValue(colorUniform_, color);
  program_->setUniformValue(morphUniform_, morph_parameter);


    // Enable or disable a generic vertex attribute array
  program_->enableAttributeArray(posAttr_);

  program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(QVector3D));

  // render primitives from array data
  glDrawElements(GL_LINES, indexBuffer.size(),
                 GL_UNSIGNED_INT, nullptr);

  program_->disableAttributeArray(posAttr_);

  // Releases the active shader program from the current QOpenGLContext.
  program_->release();

  ++frame_;
}

void CubeWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void CubeWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;

  // Rotation axis is perpendicular to the mouse position difference vector
  rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
}

void CubeWindow::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Space) {
    const auto chosen_color = QColorDialog::getColor();
    color =
        QVector4D(chosen_color.red() / 255.0f, chosen_color.green() / 255.0f,
                  chosen_color.blue() / 255.0f, 0.2f);
  }
  else{
      GLWindow::keyPressEvent(e);
  }
}

void CubeWindow::timerEvent(QTimerEvent *){

    morph_parameter += morph_direction*0.005;

    if ( (fabs(morph_parameter - 3.0f) < 0.005) || (fabs(morph_parameter - (-2.0f)) < 0.005)){
        morph_direction = morph_direction*(-1);
    }
}
} // namespace fgl