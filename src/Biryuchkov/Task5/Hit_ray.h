
#ifndef BIRYUCHKOV_HIT_RAY_H
#define BIRYUCHKOV_HIT_RAY_H

#endif //BIRYUCHKOV_HIT_RAY_H
#pragma once
#include <QVector3D>

struct Ray{
    Ray(const QVector3D o, const QVector3D d) : origin(o), direction(d){}
    QVector3D origin;
    QVector3D direction;
};