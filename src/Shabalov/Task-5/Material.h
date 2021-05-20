#pragma once
#include <QImage>
#include <QVector3D>
#include <QVector4D>
#include <utility>

struct Material {
  Material(const QVector3D &dC, const float sF, const float rI,
           const QVector4D &p)
      : diffuseColor(dC), image(nullptr), specularFactor(sF),
        refractiveIndex(rI), proportion(p) {}
  explicit Material(QImage img)
      : diffuseColor(QVector3D(0, 0, 0)), image(std::move(img)),
        specularFactor(0.0f), refractiveIndex(1), proportion(1., 0., 0., 0.) {}
  Material()
      : diffuseColor(QVector3D(0, 0, 0)), image(nullptr), specularFactor(0.0f),
        refractiveIndex(1), proportion(1., 0., 0., 0.) {}
  [[nodiscard]] auto isTexture() const noexcept { return !image.isNull(); }
  QVector3D diffuseColor;
  QImage image;
  float specularFactor;
  float refractiveIndex;
  QVector4D proportion;
};
