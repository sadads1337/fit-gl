#pragma once

#include <Base/GLWindow.hpp>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include "cube.hpp"

class UIWindow final: public fgl::GLWindow
{
public:
    using GLWindow::GLWindow;
public:
    void init() override;
    void render() override;

    void addObj(geometry::figure *f);
private:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;

    GLint posAttr_ = 0;
    QVector4D changeColor_{0.0f, 1.0f, 0.0f, 1};
    GLint matrixUniform_ = 0;
    GLint norm_ = 0;
    GLfloat ambientStrength_ = 1.0;

    QVector<geometry::figure*> figures;

    // Shader program handler.
    std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

    // Frame counter for animation.
    int frame_ = 0;

    QVector2D mousePressPosition{0., 0.};
    QVector3D rotationAxis_ = QVector3D(0.0f, 1.0f, 0.0f).normalized();
    //------buffers----
    QOpenGLBuffer vertexesBuf;
    QOpenGLBuffer indexesBuf{QOpenGLBuffer::IndexBuffer};
};
