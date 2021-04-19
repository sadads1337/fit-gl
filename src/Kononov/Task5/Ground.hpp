#pragma once

#include "Renderable.hpp"
#include "Types.hpp"

namespace Kononov {

class Ground : public Renderable {
private:
  float m_white_ref;
  float m_black_ref;

public:
  Ground(float white_ref, float black_ref);

  [[nodiscard]] std::optional<RayHit> getHit(const Ray &ray) const override;
};

} // namespace Kononov
