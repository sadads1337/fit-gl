#pragma once

#include <PositionedObject.hpp>

#include <Camera.hpp>
#include <Renderable.hpp>

namespace Kononov {

class SceneObject final : public PositionedObject {
private:
  std::shared_ptr<Renderable> m_renderable;

public:
  void render(const Camera &camera);

  [[nodiscard]] const std::shared_ptr<Renderable> &
  getRenderable() const noexcept;
  void setRenderable(const std::shared_ptr<Renderable> &renderable);
};

} // namespace Kononov
