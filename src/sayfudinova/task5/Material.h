#pragma once
#include <QVector3D>
#include <QVector4D>
#include <utility>

struct Material {
  float refractiveIndex;
  QVector4D albedo;
  QVector3D diffuseColor;
  float specularFactor;

  Material()
      : refractiveIndex(1), albedo(1., 0., 0., 0.), diffuseColor(),
        specularFactor(1) {}
  Material(const float refract, const QVector4D &a, const QVector3D &color,
           const float spec)
      : refractiveIndex(refract), albedo(a), diffuseColor(color),
        specularFactor(spec) {}
};
