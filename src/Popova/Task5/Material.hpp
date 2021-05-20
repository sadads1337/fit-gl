#pragma once
#include <QImage>
#include <QVector4D>

struct Material {

  QVector3D diffuseColor = {1., 1., 1.};
  float specularFactor = 50.;
  float refractiveIndex = 1.;
  QVector4D albedo = {1., 0., 0., 0.};
};