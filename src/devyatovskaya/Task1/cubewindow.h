#pragma once

#include <QOpenGLShaderProgram>
#include <QColorDialog>
#include <memory>
#include "mymainwindow.h"
#include "cube.h"
#include "cubeedges.h"

class CubeWindow : public MyMainWindow
{
public:
    using MyMainWindow::MyMainWindow;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    void initialize() override;
    void render() override;

private:
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;

    std::shared_ptr<QOpenGLShaderProgram> m_program;

    Cube cube {1.0f};
    CubeEdges edges {1.0f};

    QColorDialog c_dialog;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    QQuaternion rotation;

    void setRotation();
};
