#pragma once
#include <QVector3D>

struct Light{
    QVector3D position = QVector3D(0,0,0);
    float intensity = 1.0;
};
