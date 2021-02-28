#pragma once

#include <QMatrix4x4>

#include "Camera.hpp"

namespace Kononov {

class Renderable {
public:
  virtual ~Renderable() = default;
  virtual void render(Camera camera, QMatrix4x4 model_matrix) = 0;
};

} // namespace Kononov
