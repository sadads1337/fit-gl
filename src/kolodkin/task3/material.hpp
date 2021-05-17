#pragma once

#include <QVector3D>

struct Material {
  QVector3D ambient;
  QVector3D diffuse;
  QVector3D specular;
  float shininess;

  constexpr Material(QVector3D const &_ambient, QVector3D const &_diffuse,
                     QVector3D const &_specular, float _shininess)
      : ambient(_ambient), diffuse(_diffuse), specular(_specular),
        shininess(_shininess) {}
};
