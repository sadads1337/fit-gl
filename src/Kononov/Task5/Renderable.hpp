#pragma once

#include <optional>

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

  [[nodiscard]] virtual std::optional<RayHit> getHit(const Ray &ray) const = 0;
};

} // namespace Kononov
