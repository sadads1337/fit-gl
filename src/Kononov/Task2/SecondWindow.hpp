#pragma once

#include <memory>

#include <Scene/SceneWindow.hpp>

#include "SecondShader.hpp"

namespace Kononov {

class SecondWindow final : public SceneWindow {
public:
  void init() override;

  void render() override;

private:
  std::shared_ptr<SecondShader::Shader> m_cube_shader;
  std::shared_ptr<SecondShader::Shader> m_skull_shader;

  // Frame counter for animation.
  int m_frame = 0;
};

} // namespace Kononov
