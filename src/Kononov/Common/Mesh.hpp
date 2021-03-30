#pragma once

#include <QOpenGLBuffer>

#include "GLUtil.hpp"
#include "Shader.hpp"
#include "Vertex.hpp"

namespace Kononov {

class Mesh {
protected:
  virtual void bindVertexBuffer() = 0;
  virtual void releaseVertexBuffer() = 0;

public:
  virtual void drawElements() = 0;

  Mesh() = default;
  Mesh(const Mesh &) = default;
  Mesh(Mesh &&) noexcept = default;
  virtual ~Mesh() = default;
  Mesh &operator=(const Mesh &) = default;
  Mesh &operator=(Mesh &&) noexcept = default;
};

template <typename VertexType> class TypedMesh : public Mesh {
public:
  template <typename VertexInterface>
  void
  initVertexArray(TypedShader<VertexInterface> &shader,
                  const VertexMapper<VertexType, VertexInterface> &mapper) {
    bindVertexBuffer();
    shader.initVertexArray(mapper);
    releaseVertexBuffer();
  }
};

template <typename TVertex, typename TIndex>
class GenericMesh final : public TypedMesh<TVertex> {
private:
  std::unique_ptr<QOpenGLBuffer> m_vbo;
  std::unique_ptr<QOpenGLBuffer> m_ibo;
  GLenum m_primitive;
  GLsizei m_count;

  template <typename T>
  static std::unique_ptr<QOpenGLBuffer>
  makeBuffer(std::vector<T> items, QOpenGLBuffer::Type buffer_type) {
    auto buffer = std::make_unique<QOpenGLBuffer>(buffer_type);
    buffer->create();
    buffer->bind();
    buffer->allocate(reinterpret_cast<std::byte *>(items.data()),
                     static_cast<std::int32_t>(items.size() * sizeof(T)));
    buffer->release();
    return buffer;
  }

public:
  GenericMesh(const std::vector<TVertex> &vertices,
              const std::vector<TIndex> &indices, GLenum primitive)
      : m_vbo(makeBuffer(vertices, QOpenGLBuffer::VertexBuffer)),
        m_ibo(makeBuffer(indices, QOpenGLBuffer::IndexBuffer)),
        m_primitive(primitive),
        m_count(static_cast<std::int32_t>(indices.size())) {}

protected:
  void bindVertexBuffer() override { m_vbo->bind(); }
  void releaseVertexBuffer() override { m_vbo->release(); }

public:
  void drawElements() override {
    // To render we need to use concrete program, VAO and IBO (VBO is referenced
    // by VAO)
    m_ibo->bind();
    GL::requireFunctions()->glDrawElements(m_primitive, m_count,
                                           GL::typeToEnum<TIndex>(), nullptr);
    m_ibo->release();
  }
};

} // namespace Kononov
