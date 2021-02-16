#include "ShaderProgram.hpp"
#include "Kononov/Task1/FirstShader.hpp"

namespace Kononov {

ShaderProgram::ShaderProgram()
    : m_shader(std::make_unique<QOpenGLShaderProgram>()) {}

void ShaderProgram::bind() { m_shader->bind(); }

void ShaderProgram::release() { m_shader->release(); }

QOpenGLShaderProgram &ShaderProgram::getShader() const noexcept {
  return *m_shader;
}

} // namespace Kononov
