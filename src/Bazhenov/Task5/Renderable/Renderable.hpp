#ifndef FIT_GL_RENDERABLE_HPP
#define FIT_GL_RENDERABLE_HPP

#include <optional>

#include "../Geometry/Geometry.hpp"

namespace Bazhenov {

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

}

#endif // FIT_GL_RENDERABLE_HPP
