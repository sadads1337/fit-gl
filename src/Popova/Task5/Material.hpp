#pragma once
#include <QVector4D>
#include <QImage>
#include <utility>

struct Material{
    Material() : diffuseColor(), img(nullptr), specularFactor(), refractiveIndex(1), albedo(1., 0., 0., 0.){}
    Material(const QVector3D &dC, const float sF, const float  rI, const QVector4D &p) : diffuseColor(dC), img(nullptr), specularFactor(sF), refractiveIndex(rI), albedo(p){}

    QVector3D diffuseColor;
    QImage img;
    float specularFactor;
    float refractiveIndex;
    QVector4D albedo;

};