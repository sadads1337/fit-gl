#include "FirstSceneObject.hpp"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

namespace Kononov {

void FirstSceneObject::initVao() {
  const size_t stride = sizeof(GLfloat) * 8;
  const size_t pos_offset = sizeof(GLfloat) * 0;
  const size_t normal_offset = sizeof(GLfloat) * 3;
  const size_t uv_offset = sizeof(GLfloat) * 6;

  /*
   * Create and configure VAO
   */
  m_vao = std::make_unique<QOpenGLVertexArrayObject>();
  m_vao->create();
  m_vao->bind();
  m_vbo->bind();

  // glVertexAttribPointer (specify location of values in vertex structure)
  m_shader->setVertexPositionBuffer(pos_offset, stride);
  m_shader->setVertexNormalBuffer(normal_offset, stride);
  m_shader->setVertexUVBuffer(uv_offset, stride);

  m_vbo->release();
  m_vao->release();
}

std::unique_ptr<QOpenGLBuffer>
FirstSceneObject::readGLBuffer(QDataStream &stream, QOpenGLBuffer::Type type) {
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
  char *data = nullptr;
  uint size = 0;
  stream.readBytes(data, size);
  auto buffer = bufferFromData(data, size, type);
  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
  delete[] data;

  return buffer;
}

std::unique_ptr<QOpenGLBuffer>
FirstSceneObject::bufferFromData(const char *data, int size,
                                 QOpenGLBuffer::Type type) {
  auto buffer = std::make_unique<QOpenGLBuffer>(type);
  buffer->create();
  buffer->bind();
  buffer->allocate(data, size);
  buffer->release();
  return buffer;
}

FirstSceneObject::FirstSceneObject(GLenum primitive,
                                   const QString &texture_file)
    : m_primitive(primitive), m_shader_parameters(),
      m_shader(std::make_unique<FirstShader>()) {
  m_texture = std::make_unique<QOpenGLTexture>(QImage(texture_file).mirrored());
  m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
  m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

FirstSceneObject::FirstSceneObject(GLenum primitive,
                                   const QString &texture_file,
                                   const QString &geometry_file)
    : FirstSceneObject(primitive, texture_file) {
  QFile file(geometry_file);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Unable to open file " << geometry_file;
  }
  QDataStream stream(&file);
  stream.setByteOrder(QDataStream::LittleEndian);
  m_vbo = readGLBuffer(stream, QOpenGLBuffer::VertexBuffer);
  m_ibo = readGLBuffer(stream, QOpenGLBuffer::IndexBuffer);
  initVao();
}

FirstSceneObject::FirstSceneObject(GLenum primitive,
                                   const QString &texture_file,
                                   const char *vbo_data, int vbo_size,
                                   const char *ibo_data, int ibo_size)
    : FirstSceneObject(primitive, texture_file) {
  m_vbo = bufferFromData(vbo_data, vbo_size, QOpenGLBuffer::VertexBuffer);
  m_ibo = bufferFromData(ibo_data, ibo_size, QOpenGLBuffer::IndexBuffer);
  initVao();
}

void FirstSceneObject::render(QMatrix4x4 view, QMatrix4x4 model) {
  // To render we need to use concrete program, VAO and IBO (VBO is referenced
  // by VAO)
  m_shader->bind();
  m_vao->bind();
  m_ibo->bind();
  m_texture->bind();

  m_shader->setMatrices(view, model);
  m_shader->setParameters(m_shader_parameters);

  // glEnableVertexAttribArray (allow current VAO to affect attribute)
  m_shader->enableAttributeArrays();

  const size_t count = m_ibo->size() / sizeof(GLuint);
  QOpenGLContext::currentContext()->functions()->glDrawElements(
      m_primitive, count, GL_UNSIGNED_INT, nullptr);

  // glDisableVertexAttribArray (because it is not bound to m_program ??? and
  // can affect further rendering)
  m_shader->disableAttributeArrays();

  m_texture->release();
  m_ibo->release();
  m_vao->release();
  m_shader->release();
}

const FirstShaderParameters &FirstSceneObject::getShaderParameters() const {
  return m_shader_parameters;
}

FirstShaderParameters &FirstSceneObject::getShaderParameters() {
  return m_shader_parameters;
}

void FirstSceneObject::setShaderParameters(
    const FirstShaderParameters &shader_parameters) {
  m_shader_parameters = shader_parameters;
}

} // namespace Kononov
