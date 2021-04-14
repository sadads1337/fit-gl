#pragma once

#include "Renderable.hpp"
#include "Types.hpp"

namespace Kononov {

class Ground : public Renderable {
private:
  float m_white_ref;
  float m_black_ref;

public:
  explicit Ground(float white_ref, float black_ref);

  bool getHit(const Ray &ray, RayHit &hit) const override;
};

} // namespace Kononov
