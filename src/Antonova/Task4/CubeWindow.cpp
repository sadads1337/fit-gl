#include "CubeWindow.hpp"
#include <QScreen>
#include <QtMath>
#include <iostream>
#include <vector>

namespace fgl {

void CubeWindow::makeCube(const float side_size, const int n_points) {

  auto side_half = side_size / 2.0f;
  auto step = side_size / float(n_points - 1);
  auto texture_step = 1.0f / float(n_points - 1);

  std::vector<VertexData> vertices;
  vertices.reserve(6 * pow(n_points, 2));

  // bottom and top
    for (auto z = -1; z <= 1; z += 2) {
        for (auto j = 0; j < n_points; j++) {
            for (auto i = 0; i < n_points; i++) {
                vertices.emplace_back(VertexData{
                        QVector3D(z*(-side_half + i * step), -side_half + j * step, z * side_half),
                        QVector3D(0.0f, 0.0f, z),
                        QVector2D(i * texture_step, j * texture_step),
                        QVector3D(z, 0.0f, 0.0f)});
            }
        }
    }

    // left and right
    for (auto x = -1; x <= 1; x += 2) {
        for (auto k = 0; k < n_points; k++) {
            for (auto j = 0; j < n_points; j++) {
                vertices.emplace_back(VertexData{
                        QVector3D(x * side_half, -side_half + j * step, x*(- side_half + k * step)),
                        QVector3D(x, 0.0f, 0.0f),
                        QVector2D(j * texture_step, k * texture_step),
                        QVector3D(0.0f, x, 0.0f)});
            }
        }
    }

    // back and front
    for (auto y = -1; y <= 1; y += 2) {
        for (auto i = 0; i < n_points; i++) {
            for (auto k = 0; k < n_points; k++) {
                vertices.emplace_back(VertexData{
                        QVector3D(-side_half + i * step, y * side_half, y*(- side_half + k * step)),
                        QVector3D(0.0f, y, 0.0f),
                        QVector2D(k * texture_step, i * texture_step),
                        QVector3D(y, 0.0f, 0.0f)});
            }
        }
    }

  std::vector<GLuint> indices;
  int cube_indices = 36 * pow(n_points - 1, 2);
  indices.reserve(cube_indices);

  for (int i = 0; i < 6 * pow(n_points, 2); i += n_points * n_points) {
    for (int j = 0; j < (n_points - 1) * (n_points - 1); j += n_points) {
      for (int k = 0; k < (n_points - 1); k++) {
        indices.emplace_back(i + j + k + n_points);
        indices.emplace_back(i + j + k + 0);
        indices.emplace_back(i + j + k + n_points + 1);
        indices.emplace_back(i + j + k + n_points + 1);
        indices.emplace_back(i + j + k + 0);
        indices.emplace_back(i + j + k + 1);
      }
    }
  }

  vertexBuffer.create();
  vertexBuffer.bind();
  vertexBuffer.allocate(vertices.data(),
                        static_cast<int>(vertices.size() * sizeof(VertexData)));

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indices.data(),
                       static_cast<int>(indices.size() * sizeof(GLuint)));
}

void CubeWindow::initTexture() {
    texture = std::make_shared<QOpenGLTexture>(QImage(":/Texture/t.jpg").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Linear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);

    normalMap = std::make_shared<QOpenGLTexture>(QImage(":/Texture/n.jpg").mirrored());

    normalMap->setMinificationFilter(QOpenGLTexture::Linear);
    normalMap->setMagnificationFilter(QOpenGLTexture::Linear);
    normalMap->setWrapMode(QOpenGLTexture::Repeat);
}

void CubeWindow::init() {
  program_ = std::make_unique<QOpenGLShaderProgram>(this);

  program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/cube.vs");
  program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/Shaders/cube.fs");

  program_->link();

  // attributes
  posAttr_ = program_->attributeLocation("posAttr");
  Q_ASSERT(posAttr_ != -1);
  normAttr_ = program_->attributeLocation("normAttr");
  Q_ASSERT(normAttr_ != -1);
  textureAttr_ = program_->attributeLocation("textureAttr");
  Q_ASSERT(textureAttr_ != -1);
  tangentAttr_ = program_->attributeLocation("tangentAttr");
  Q_ASSERT(tangentAttr_ != -1);

  // uniforms
  model_matrixUniform_ = program_->uniformLocation("model_matrix");
  Q_ASSERT(model_matrixUniform_ != -1);
  view_matrixUniform_ = program_->uniformLocation("view_matrix");
  Q_ASSERT(view_matrixUniform_ != -1);
  projection_matrixUniform_ = program_->uniformLocation("projection_matrix");
  Q_ASSERT(projection_matrixUniform_ != -1);

  colorUniform_ = program_->uniformLocation("cubeColor");
  Q_ASSERT(colorUniform_ != -1);
  morphUniform_ = program_->uniformLocation("morph");
  Q_ASSERT(morphUniform_ != -1);
  lightPosUniform_ = program_->uniformLocation("lightPos");
  Q_ASSERT(lightPosUniform_ != -1);
  viewPosUniform_ = program_->uniformLocation("viewPos");
  Q_ASSERT(viewPosUniform_ != -1);
  lightColorUniform_ = program_->uniformLocation("lightColor");
  Q_ASSERT(lightColorUniform_ != -1);
  textureUniform_ = program_->uniformLocation("texture");
  Q_ASSERT(textureUniform_ != -1);
  normalMapUniform_ = program_->uniformLocation("normalMap");
  Q_ASSERT(normalMapUniform_ != -1);

  initTexture();
  // init one cube
  makeCube(cube_side_size, 20);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  timer.start(20, this);
}


void CubeWindow::render() {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const auto retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  program_->bind();

  auto cubes_grid_half = (cubes_grid_size - 1) * 3 * cube_side_size / 2.0f;
  auto cubes_grid_step = 3 * cube_side_size;

  for (auto cube_y = -cubes_grid_half; cube_y <= cubes_grid_half;
       cube_y += cubes_grid_step) {
    for (auto cube_x = -cubes_grid_half; cube_x <= cubes_grid_half;
         cube_x += cubes_grid_step) {

      QMatrix4x4 model_matrix;
      QMatrix4x4 view_matrix;
      QMatrix4x4 projection_matrix;

      projection_matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

      model_matrix.translate(cube_x, cube_y, -9);
      model_matrix.rotate(10.0 * frame_ / screen()->refreshRate(),
                          rotationAxis);

      program_->setUniformValue(model_matrixUniform_, model_matrix);
      program_->setUniformValue(view_matrixUniform_, view_matrix);
      program_->setUniformValue(projection_matrixUniform_, projection_matrix);
      program_->setUniformValue(colorUniform_, cubeColor);
      program_->setUniformValue(morphUniform_, morph_parameter);
      program_->setUniformValue(lightPosUniform_, lightPosition);
      program_->setUniformValue(viewPosUniform_, viewPosition);
      program_->setUniformValue(lightColorUniform_, lightColor);

      texture->bind(0);
      program_->setUniformValue(textureUniform_, 0);
      normalMap->bind(1);
      program_->setUniformValue(normalMapUniform_, 1);

      vertexBuffer.bind();

      float offset = 0;
      program_->enableAttributeArray(posAttr_);
      program_->setAttributeBuffer(posAttr_, GL_FLOAT, offset, 3,
                                   sizeof(VertexData));
      offset += sizeof(QVector3D);
      program_->enableAttributeArray(normAttr_);
      program_->setAttributeBuffer(normAttr_, GL_FLOAT, offset, 3,
                                   sizeof(VertexData));
      offset += sizeof(QVector3D);
      program_->enableAttributeArray(textureAttr_);
      program_->setAttributeBuffer(textureAttr_, GL_FLOAT, offset, 2,
                                   sizeof(VertexData));

      offset += sizeof(QVector2D);
      program_->enableAttributeArray(tangentAttr_);
      program_->setAttributeBuffer(tangentAttr_, GL_FLOAT, offset, 3,
                                   sizeof(VertexData));

      indexBuffer.bind();

      // render primitives from array data
      glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, nullptr);

      program_->disableAttributeArray(posAttr_);
      program_->disableAttributeArray(normAttr_);
      program_->disableAttributeArray(textureAttr_);
      program_->disableAttributeArray(tangentAttr_);

    }
  }

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
    cubeColor =
        QVector3D(chosen_color.red() / 255.0f, chosen_color.green() / 255.0f,
                  chosen_color.blue() / 255.0f);
  } else {
    GLWindow::keyPressEvent(e);
  }
}

void CubeWindow::timerEvent(QTimerEvent *) {

  morph_parameter += morph_direction * 0.005;

  if ((fabs(morph_parameter - 1.0f) < 0.0005) ||
      (fabs(morph_parameter - 0.0f) < 0.0005)) {
    morph_direction = morph_direction * (-1);
  }
}
} // namespace fgl