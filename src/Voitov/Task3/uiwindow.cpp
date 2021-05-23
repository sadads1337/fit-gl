#include "uiwindow.h"
#include<iostream>
#include <QScreen>

void UIWindow::init()
{
    // Enable depth test and face culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vertexesBuf.create();
    indexesBuf.create();
    vertexesBuf.bind();
    indexesBuf.bind();

    vertexesBuf.allocate(this->figures[0]->getVertexes().data(),
                         static_cast<std::int32_t>(
                             this->figures[0]->getVertexes().size() * sizeof(decltype(this->figures[0]->getVertexes())::value_type)));

    indexesBuf.allocate(this->figures[0]->getIndexes().data(),
                        static_cast<std::int32_t>(
                           this->figures[0]->getIndexes().size() * sizeof(decltype(this->figures[0]->getIndexes())::value_type)));

    program_ = std::make_unique<QOpenGLShaderProgram>(this);
    program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vshader.vs");
    program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fshader.fs");
    program_->link();

    posAttr_ = program_->attributeLocation("v_pos");
    matrixUniform_ = program_->uniformLocation("MVPMatrix");
    norm_ = program_->attributeLocation("normal");
    ambientStrength_ = program_->uniformLocation("ambientStrength");

    program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, sizeof(geometry::VertexData));
    program_->setAttributeBuffer(norm_, GL_FLOAT, sizeof(QVector3D), 3,
                                 sizeof(geometry::VertexData));
}

void UIWindow::render()
{
    const auto retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program_->bind();

    QMatrix4x4 matrix0;
    //QMatrix4x4 model0;
    matrix0.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);

    matrix0.translate(figures[0]->getCenter());
    matrix0.scale(0.3f, 0.3f, 0.3f);

    // Set attrs and unis
    program_->setUniformValue(matrixUniform_, matrix0);
    program_->setUniformValue(ambientStrength_, 1.0f);

    program_->setUniformValue("qt_color_set", QVector4D{1.0f, 1.0f, 1.0f, 1});
    program_->setUniformValue("normalMatrix", matrix0.normalMatrix());
    program_->setUniformValue("modeChange", 0);//GOURAUD -> 0 or PHONG -> 1
    program_->enableAttributeArray(norm_);
    program_->enableAttributeArray(posAttr_);

    // Draw
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);

    program_->disableAttributeArray(posAttr_);
    program_->disableAttributeArray(norm_);

    for (int k = 1; k < 9; k++) {
      // Calculate MVP
      QMatrix4x4 matrix;
      matrix.perspective(60.0f, (float)width() / height(), 0.1f, 100.0f);
      matrix.translate(figures[k]->getCenter());
      matrix.rotate(10.0 * (k + 1) * frame_ / screen()->refreshRate(),
                    rotationAxis_);
      matrix.scale(0.3f, 0.3f, 0.3f);
      // Set attrs and unis
      program_->setUniformValue(ambientStrength_, 0.1f);
      program_->setUniformValue(matrixUniform_, matrix);
      program_->setUniformValue("normalMatrix", matrix.normalMatrix());
      program_->setUniformValue("qt_color_set", changeColor_);

      program_->enableAttributeArray(norm_);
      program_->enableAttributeArray(posAttr_);

      // Draw
      glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, nullptr);

      program_->disableAttributeArray(posAttr_);
      program_->disableAttributeArray(norm_);
    }
    program_->release();
    ++frame_;
}

void UIWindow::addObj(geometry::figure *f)
{
    this->figures.append(f);
}

void UIWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_C) {
    QColor color = QColorDialog::getColor();
    changeColor_ = QVector4D(color.red() / 255.0, color.green() / 255.0,
                             color.blue() / 255.0, 1);
  }
  if (event->key() == Qt::Key_B) {
    QColor color = QColorDialog::getColor();
    glClearColor(color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0, 1);
  }
}

void UIWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
}

void UIWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;
  if((diff.x() != 0) | (diff.y() != 0)){
      rotationAxis_ = QVector3D(diff.y(), diff.x(), 0.0f).normalized();
  }
}
