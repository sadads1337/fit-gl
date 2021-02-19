#pragma once

#include <memory>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QString>

#include <MeshBuffers.hpp>

#include "FirstShader.hpp"

namespace Kononov {

class FirstRenderable {
private:
  FirstShaderParameters m_shader_parameters;
  std::shared_ptr<FirstShader> m_shader;
  std::unique_ptr<QOpenGLTexture> m_texture;
  std::unique_ptr<MeshBuffers<Vertex, GLuint>> m_mesh;

  FirstRenderable(const QString &texture_file,
                  std::shared_ptr<FirstShader> &shader);

public:
  FirstRenderable(GLenum primitive, std::shared_ptr<FirstShader> &shader,
                  const QString &texture_file, const QString &geometry_file);
  FirstRenderable(GLenum primitive, std::shared_ptr<FirstShader> &shader,
                  const QString &texture_file,
                  const std::vector<Vertex> &vertices,
                  const std::vector<GLuint> &indices);

  void render(QMatrix4x4 view, QMatrix4x4 model);

  [[nodiscard]] const FirstShaderParameters &
  getShaderParameters() const noexcept;
  [[nodiscard]] FirstShaderParameters &getShaderParameters() noexcept;
  void setShaderParameters(const FirstShaderParameters &shader_parameters);
};

} // namespace Kononov
