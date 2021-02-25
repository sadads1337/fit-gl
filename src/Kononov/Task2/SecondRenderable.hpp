#pragma once

#include <memory>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QString>

#include <MeshBuffers.hpp>
#include <Renderable.hpp>

#include "SecondShader.hpp"

namespace Kononov {

class SecondRenderable : public Renderable {
private:
  SecondShaderParameters m_shader_parameters;
  std::shared_ptr<SecondShader> m_shader;
  std::unique_ptr<QOpenGLTexture> m_texture;
  std::unique_ptr<MeshBuffers<Vertex, GLuint>> m_mesh;

  SecondRenderable(const QString &texture_file,
                  std::shared_ptr<SecondShader> &shader);

public:
  SecondRenderable(GLenum primitive, std::shared_ptr<SecondShader> &shader,
                  const QString &texture_file, const QString &geometry_file);
  SecondRenderable(GLenum primitive, std::shared_ptr<SecondShader> &shader,
                  const QString &texture_file,
                  const std::vector<Vertex> &vertices,
                  const std::vector<GLuint> &indices);

  void render(Camera camera, QMatrix4x4 model_matrix) override;

  [[nodiscard]] const SecondShaderParameters &
  getShaderParameters() const noexcept;
  [[nodiscard]] SecondShaderParameters &getShaderParameters() noexcept;
  void setShaderParameters(const SecondShaderParameters &shader_parameters);
};

} // namespace Kononov
