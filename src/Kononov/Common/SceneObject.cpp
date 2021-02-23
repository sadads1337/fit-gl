#include "SceneObject.hpp"

namespace Kononov {

void SceneObject::render(const Camera &camera) {
  if (m_renderable != nullptr) {
    m_renderable->render(camera, getAbsoluteTransformMatrix());
  }
}

const std::shared_ptr<Renderable> &SceneObject::getRenderable() const noexcept {
  return m_renderable;
}

void SceneObject::setRenderable(
    const std::shared_ptr<Renderable> &renderable) {
  m_renderable = renderable;
}

} // namespace Kononov
