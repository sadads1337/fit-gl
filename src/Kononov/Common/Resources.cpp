#include "Resources.hpp"

#include <stdexcept>
#include <unordered_map>

#include <QFileInfo>

namespace {

// NOLINTNEXTLINE(cert-err58-cpp)
const std::unordered_map<QString, QOpenGLShader::ShaderType> ext_type_map = {
    {"vert", QOpenGLShader::Vertex},
    {"vs", QOpenGLShader::Vertex},
    {"tesc", QOpenGLShader::TessellationControl},
    {"cs", QOpenGLShader::TessellationControl},
    {"tese", QOpenGLShader::TessellationEvaluation},
    {"es", QOpenGLShader::TessellationEvaluation},
    {"geom", QOpenGLShader::Geometry},
    {"gs", QOpenGLShader::Geometry},
    {"frag", QOpenGLShader::Fragment},
    {"fs", QOpenGLShader::Fragment},
    {"comp", QOpenGLShader::Compute},
};

} // namespace

namespace Kononov {

std::unique_ptr<QOpenGLTexture>
Resources::loadTexture(const QString &filename) {
  auto texture = std::make_unique<QOpenGLTexture>(QImage(filename).mirrored());
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
  return texture;
}

std::shared_ptr<QOpenGLTexture>
Resources::loadTextureShared(const QString &filename) {
  return loadTexture(filename);
}

std::unique_ptr<QOpenGLShaderProgram>
Resources::loadShaderProgram(const std::vector<QString> &files) {
  auto res = std::make_unique<QOpenGLShaderProgram>();
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

    if (!res->addShaderFromSourceFile(it->second, name)) {
      throw std::runtime_error("Failed to load shader sources");
    }
  }

  if (!res->link()) {
    throw std::runtime_error("Failed to compile shader");
  }

  return res;
}

std::shared_ptr<QOpenGLShaderProgram>
Resources::loadShaderProgramShared(const std::vector<QString> &files) {
  return loadShaderProgram(files);
}

} // namespace Kononov