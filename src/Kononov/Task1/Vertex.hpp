#pragma once

#include <QVector3D>
#include <QVector2D>

namespace Kononov {

struct Vertex {
  QVector3D position;
  QVector3D normal;
  QVector2D uv;
};

} // namespace Kononov
