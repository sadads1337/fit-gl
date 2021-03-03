#pragma once

#include "cube.hpp"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QBasicTimer>
#include <QColorDialog>
#include <memory>

class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
Q_OBJECT

public:

    CubeWidget() = delete;
    CubeWidget(QWidget* parent = nullptr);


public slots:
    void setMorphFactor(float val);
    void setColor(QColor const& color);
    void setCurrentFace(int face);
    void setFaceMode();
    void setEdgeMode();
    void makeNewGrid(int grid_steps);

protected:
    inline static const QColor initFaceColor = Qt::GlobalColor::lightGray;
    inline static const QColor initEdgeColor = Qt::GlobalColor::darkGray;
    inline static const QVector3D initSize = {2.f, 2.f, 2.f};
    inline static const int initSteps = 8;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *ev) override;
    void timerEvent(QTimerEvent *e) override;
    QSize minimumSizeHint() const override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();


private:
    //using QOpenGLWidget::QOpenGLWidget;
    enum class colorMode{
        face,
        edge
    };
    colorMode  mode_ = colorMode::face;
    int currentFace_ = -1;
    float morphFactor = 0.f;

    std::unique_ptr<Cube> pCube_ = nullptr;

    QOpenGLShaderProgram program;
    QBasicTimer timer;
    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector2D mouseLastPosition;

    QVector3D rotationAxis;
    qreal angularSpeed = 0;
    qreal zDistance = - 5.f;
    QQuaternion rotation;
};

