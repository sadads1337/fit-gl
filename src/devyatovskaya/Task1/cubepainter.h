#pragma once
#include "GeometryPainter.h"

class CubePainter : public GeometryPainter {
public:
  CubePainter(Geometry &geometry) : GeometryPainter{geometry} {}

  void setUniformColor(const QColor &color) override;
};
