#pragma once

#include <QVector3D>
#include <QMatrix4x4>

class cameraView
{
    QVector3D position_;
    QVector3D center_;
    QVector3D up_;

public:
    cameraView(QVector3D position, QVector3D center, QVector3D up);
    QMatrix4x4 getViewMatrix();

};

