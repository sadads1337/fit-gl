#pragma once

#include <Base/GLWindow.hpp>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QVector3D>

#include "cube.hpp"

#include <memory>//std::unique_ptr

class UIWindow final: public fgl::GLWindow
{
public:
    using GLWindow::GLWindow;
public:
    void init() override;
    void render() override;

    void addObj(std::unique_ptr<geometry::figure> &f);
private:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;

    // Attributes and uniforms handlers.
    GLint posAttr_ = 0;
    //QVector4D backColor{1.0, 1.0, 1.0, 1};
    GLint matrixUniform_ = 0;

    std::unique_ptr<geometry::figure> figure;//changed

    // Shader program handler.
    std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

    // Frame counter for animation.
    int frame_ = 0;

    QVector2D mousePressPosition{0., 0.};
    //------buffers----
    QOpenGLBuffer vertexesBuf;
    QOpenGLBuffer indexesBuf{QOpenGLBuffer::IndexBuffer};
};
