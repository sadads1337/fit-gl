#pragma once

#include <memory>

#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace Kononov {

class Renderable {
public:
  Renderable() = default;
  Renderable(const Renderable &) = default;
  Renderable(Renderable &&) noexcept = default;
  virtual ~Renderable() = default;
  Renderable &operator=(const Renderable &) = default;
  Renderable &operator=(Renderable &&) noexcept = default;

  virtual void render(Camera camera, QMatrix4x4 model_matrix) = 0;
};

class GenericRenderable : public Renderable {
private:
  std::shared_ptr<Shader> m_shader;
  std::shared_ptr<Mesh> m_mesh;
  std::unique_ptr<QOpenGLVertexArrayObject> m_vao;

public:
  template <typename VertexInterface, typename VertexType>
  GenericRenderable(const std::shared_ptr<TypedShader<VertexInterface>> &shader,
                    const std::shared_ptr<TypedMesh<VertexType>> &mesh)
      : m_shader(shader), m_mesh(mesh),
        m_vao(std::make_unique<QOpenGLVertexArrayObject>()) {
    m_vao->create();
    m_vao->bind();
    mesh->initVertexArray(*shader, VertexMapper<VertexType, VertexInterface>());
    m_vao->release();
  }

  void render(Camera camera, QMatrix4x4 model_matrix) override {
    m_shader->bind();
    m_shader->prepare(camera, model_matrix);
    m_vao->bind();
    m_mesh->drawElements();
    m_vao->release();
    m_shader->cleanup();
    m_shader->release();
  }
};

} // namespace Kononov
