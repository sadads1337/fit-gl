#pragma once

#include <PositionedObject.hpp>

#include <Camera.hpp>

#include "FirstRenderable.hpp"

namespace Kononov {

class FirstSceneObject : public PositionedObject {
private:
  std::shared_ptr<FirstRenderable> m_renderable;

public:
  void render(const Camera &camera);

  [[nodiscard]] const std::shared_ptr<FirstRenderable> &
  getRenderable() const noexcept;
  void setRenderable(const std::shared_ptr<FirstRenderable> &renderable);
};

} // namespace Kononov
