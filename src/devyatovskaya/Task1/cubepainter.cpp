#include "cubepainter.h"
#include <QColor>

void CubePainter::setUniformColor(const QColor &color) {
  auto &color_array = geometry_.ColorArray();

  qreal r = 0, g = 0, b = 0;
  color.getRgbF(&r, &g, &b);

  for (unsigned i = 0; i < color_array.size(); i += 3) {
    color_array[i] = r;
    color_array[i + 1] = g;
    color_array[i + 2] = b;
  }
}
