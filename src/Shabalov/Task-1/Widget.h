//
// Created by nikita on 19.02.2021.
//

#ifndef TASK_1_WIDGET_H
#define TASK_1_WIDGET_H


#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimerEvent>
#include <QBasicTimer>
#include "Object3D.h"

class Widget : public QOpenGLWidget
{
Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void setXRotation(float angle);
    void setYRotation(float angle);
    void setZRotation(float angle);
    void setColor(QColor color);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void initShaders();
    void initCube(float width);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);
signals:
    void xRotationChanged(float angle);
    void yRotationChanged(float angle);
    void zRotationChanged(float angle);
    void ColorChanged(QColor color);

private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QVector2D m_mousePosition;
    QQuaternion m_rotation;

    float x_rot;
    float y_rot;
    float z_rot;

    QVector<Object3D *> m_objects;

    QColor m_color;

    float m_z;
    QBasicTimer m_timer;
    float angleObject;
};


#endif //TASK_1_WIDGET_H
