#pragma once
#include <QVector4D>
#include <QImage>
#include <utility>

struct Material{
    Material(const QVector3D &dC, const float sF, const float  rI, const QVector4D &p) : diffuseColor(dC), specularFactor(sF), refractiveIndex(rI), proportion(p), img(nullptr){}
    explicit Material(QImage i) : img(std::move(i)), refractiveIndex(1), proportion(1., 0., 0., 0.){}
    Material() : refractiveIndex(1), proportion(1., 0., 0., 0.), img(nullptr), diffuseColor(), specularFactor(){}
    [[nodiscard]] bool isTexture() const {
        if(img.isNull()) return false;
        return true;
    }
    QVector3D diffuseColor;
    float specularFactor{};
    float refractiveIndex;
    QVector4D proportion;
    QImage img;

};
