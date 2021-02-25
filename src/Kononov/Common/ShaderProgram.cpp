#include "ShaderProgram.hpp"

#include <stdexcept>

#include <QFileInfo>
#include <QOpenGLShader>

namespace {

// NOLINTNEXTLINE(cert-err58-cpp)
const std::unordered_map<QString, QOpenGLShader::ShaderType> ext_type_map = {
    {"vert", QOpenGLShader::Vertex},
    {"vs", QOpenGLShader::Vertex},
    {"tesc", QOpenGLShader::TessellationControl},
    {"tese", QOpenGLShader::TessellationEvaluation},
    {"geom", QOpenGLShader::Geometry},
    {"frag", QOpenGLShader::Fragment},
    {"fs", QOpenGLShader::Fragment},
    {"comp", QOpenGLShader::Compute},
};

} // namespace

namespace Kononov {

ShaderProgramBase::ShaderProgramBase(const std::vector<QString> &files)
    : m_shader(std::make_unique<QOpenGLShaderProgram>()) {
  for (const auto &name : files) {
    QFileInfo info(name);
    if (!info.exists()) {
      throw std::invalid_argument("File not found");
    }
    auto ext = info.suffix();
    auto it = ext_type_map.find(ext);
    if (it == ext_type_map.end()) {
      throw std::invalid_argument("Unknown shader file extension");
    }

    if (!m_shader->addShaderFromSourceFile(it->second, name)) {
      throw std::runtime_error("Failed to load shader sources");
    }
  }

  if (!m_shader->link()) {
    throw std::runtime_error("Failed to compile shader");
  }
}

QOpenGLShaderProgram &ShaderProgramBase::getShader() const noexcept {
  return *m_shader;
}

GLint ShaderProgramBase::getAttributeLocation(const QString &name) const {
  return m_shader->attributeLocation(name);
}

GLint ShaderProgramBase::getUniformLocation(const QString &name) const {
  return m_shader->uniformLocation(name);
}

} // namespace Kononov