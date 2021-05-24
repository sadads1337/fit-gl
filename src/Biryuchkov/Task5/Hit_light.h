

#ifndef BIRYUCHKOV_HIT_LIGHT_H
#define BIRYUCHKOV_HIT_LIGHT_H

#endif //BIRYUCHKOV_HIT_LIGHT_H
#pragma once
#include <QVector3D>

struct Light{
    Light(const QVector3D &p, const float i) : position(p), intensity(i){}
    QVector3D position;
    float intensity;
};