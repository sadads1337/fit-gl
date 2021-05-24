
#ifndef BIRYUCHKOV_MATERIAL_H
#define BIRYUCHKOV_MATERIAL_H

#endif //BIRYUCHKOV_MATERIAL_H
#pragma once
#include <QVector4D>
#include <QImage>
#include <utility>

struct Material{
    Material(const QVector3D &dC, const float sF, const float  rI, const QVector4D &p) : diffuseColor(dC), img(nullptr), specularFactor(sF), refractiveIndex(rI), proportion(p){}
    explicit Material(QImage i) : img(std::move(i)), refractiveIndex(1), proportion(1., 0., 0., 0.){}
    Material() : diffuseColor(), img(nullptr), specularFactor(), refractiveIndex(1), proportion(1., 0., 0., 0.){}
    [[nodiscard]] bool isTexture() const {
        if(img.isNull()) return false;
        return true;
    }
    QVector3D diffuseColor;
    QImage img;
    float specularFactor{};
    float refractiveIndex;
    QVector4D proportion;

};