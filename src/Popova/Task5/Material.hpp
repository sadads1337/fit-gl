#pragma once
#include <QVector4D>
#include <QImage>

struct Material{
    Material() : diffuseColor(), specularFactor(), refractiveIndex(1), albedo(1., 0., 0., 0.){}
    Material(const QVector3D &dC, const float sF, const float  rI, const QVector4D &p) : diffuseColor(dC), specularFactor(sF), refractiveIndex(rI), albedo(p){}

    QVector3D diffuseColor;
    float specularFactor;
    float refractiveIndex;
    QVector4D albedo;
};