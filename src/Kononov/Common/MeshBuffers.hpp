#pragma once

#include <memory>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "GLUtil.hpp"
#include "ShaderProgram.hpp"

namespace Kononov {

template <typename TVertex, typename TIndex> class MeshBuffers final {
private:
  std::unique_ptr<QOpenGLBuffer> m_vbo;
  std::unique_ptr<QOpenGLBuffer> m_ibo;
  std::unique_ptr<QOpenGLVertexArrayObject> m_vao;
  GLenum m_primitive;
  GLsizei m_count;

  template <typename T>
  static std::unique_ptr<QOpenGLBuffer>
  makeBuffer(std::vector<T> items, QOpenGLBuffer::Type buffer_type) {
    auto buffer = std::make_unique<QOpenGLBuffer>(buffer_type);
    buffer->create();
    buffer->bind();
    buffer->allocate(reinterpret_cast<std::byte *>(items.data()),
                     items.size() * sizeof(T));
    buffer->release();
    return buffer;
  }

public:
  MeshBuffers(const std::vector<TVertex> &vertices,
              const std::vector<TIndex> &indices, GLenum primitive)
      : m_vbo(makeBuffer(vertices, QOpenGLBuffer::VertexBuffer)),
        m_ibo(makeBuffer(indices, QOpenGLBuffer::IndexBuffer)),
        m_vao(std::make_unique<QOpenGLVertexArrayObject>()),
        m_primitive(primitive), m_count(indices.size()) {
    m_vao->create();
  }

  void setupVao(ShaderProgram<TVertex> &shader) {
    m_vao->bind();
    m_vbo->bind();
    shader.setupCurrentVao();
    m_vbo->release();
    m_vao->release();
  }

  void drawElements() {
    // To render we need to use concrete program, VAO and IBO (VBO is referenced
    // by VAO)
    m_vao->bind();
    m_ibo->bind();
    GLUtil::requireFunctions()->glDrawElements(m_primitive, m_count,
                                               glTypeToEnum<TIndex>(), nullptr);
    m_ibo->release();
    m_vao->release();
  }
};

} // namespace Kononov
