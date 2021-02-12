#include "FirstSceneObject.hpp"

namespace Kononov {

void FirstSceneObject::render(const Camera &camera) {
  if (m_renderable == nullptr) {
    return;
  }

  m_renderable->getShaderParameters().setViewPos(camera.getAbsolutePosition());
  m_renderable->render(camera.getProjectionViewMatrix(),
                       getAbsoluteTransformMatrix());
}

const std::shared_ptr<FirstRenderable> &
FirstSceneObject::getRenderable() const {
  return m_renderable;
}

void FirstSceneObject::setRenderable(
    const std::shared_ptr<FirstRenderable> &renderable) {
  m_renderable = renderable;
}

} // namespace Kononov
