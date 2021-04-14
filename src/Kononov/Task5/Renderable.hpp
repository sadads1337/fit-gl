#pragma once

#include "Geometry.hpp"

namespace Kononov {

class Renderable {
public:
  Renderable() = default;
  Renderable(const Renderable &) = default;
  Renderable(Renderable &&) noexcept = default;
  virtual ~Renderable() = default;
  Renderable &operator=(const Renderable &) = default;
  Renderable &operator=(Renderable &&) noexcept = default;

  virtual bool getHit(const Ray &ray, RayHit &hit) const = 0;
};

} // namespace Kononov