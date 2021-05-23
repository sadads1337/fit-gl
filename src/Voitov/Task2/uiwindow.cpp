#include "uiwindow.h"
#include<iostream>

void UIWindow::init()
{
    // Enable depth test and face culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    start_ = std::chrono::system_clock::now();

    vertexesBuf.create();
    indexesBuf.create();
    vertexesBuf.bind();
    indexesBuf.bind();

    vertexesBuf.allocate(this->figures->getVertexes().cbegin(),
                         static_cast<std::int32_t>(this->figures->getVertexes().size() * sizeof(QVector3D)));

    indexesBuf.allocate(this->figures->getIndexes().cbegin(),
                 static_cast<std::int32_t>(this->figures->getIndexes().size() * sizeof(GLint)));


    program_ = std::make_unique<QOpenGLShaderProgram>(this);
    program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vshader.vs");
    program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fshader.fs");
    program_->link();

    posAttr_ = program_->attributeLocation("posAttr");
    Q_ASSERT(posAttr_ != -1);

    matrixUniform_ = program_->uniformLocation("matrix");
    Q_ASSERT(matrixUniform_ != -1);
}

void UIWindow::render()
{
    time_ = std::chrono::system_clock::now() - start_;

    const auto retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -4);//camera
    matrix.rotate(speed * frame_ / 100, this->figures->getRotationAxis());

    program_->bind();
    program_->setUniformValue(matrixUniform_, matrix);
    program_->setUniformValue("col", this->figures->getColor());
    program_->setAttributeBuffer(posAttr_, GL_FLOAT, 0, 3, 3*sizeof(GLfloat));//in posAttr with shift=0, tuple_size=3, and step (default=0)

    program_->setUniformValue("time", time_.count());

    program_->enableAttributeArray(posAttr_);
    glDrawElements(GL_LINE_STRIP, static_cast<GLsizei>(this->figures->getIndexes().size()), GL_UNSIGNED_INT, nullptr);

    program_->disableAttributeArray(posAttr_);
    program_->release();
    ++frame_;
}

void UIWindow::addObj(geometry::figure *f)
{
    this->figures = f;
}

void UIWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_C) {
    QColor color = QColorDialog::getColor();
    this->figures->setColor(QVector3D(color.red(), color.green(), color.blue()));
  }
  if (event->key() == Qt::Key_B) {
    QColor color = QColorDialog::getColor();
    glClearColor(color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0, 1);
  }
}

void UIWindow::mousePressEvent(QMouseEvent *e) {
  // Save mouse press position
  mousePressPosition = QVector2D(e->localPos());
  speed = 100.0;
}

void UIWindow::mouseReleaseEvent(QMouseEvent *e) {
  // Mouse release position - mouse press position
  const auto diff = QVector2D(e->localPos()) - mousePressPosition;
  this->figures->setRotationAxis(QVector3D(diff.y(), diff.x(), 0.0).normalized());
}
