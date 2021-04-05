#pragma once

#include <memory>

#include <Scene/SceneWindow.hpp>
#include <SceneObject.hpp>

namespace Kononov {

class MainWindow final : public SceneWindow {
public:
  void init() override;

  void render() override;

private:
  std::shared_ptr<SceneObject> m_skull;
  std::shared_ptr<SceneObject> m_skull_rotating;
  std::shared_ptr<SceneObject> m_cube;

  // Frame counter for animation.
  int m_frame = 0;
};

} // namespace Kononov
