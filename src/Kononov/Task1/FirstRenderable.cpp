#include "FirstRenderable.hpp"

#include <QDataStream>
#include <QDebug>
#include <QFile>

#include <GLUtil.hpp>

namespace {

template <typename T> std::vector<T> readVector(QDataStream &stream) {
  std::vector<T> res;
  uint32_t length = 0;
  stream >> length;
  if (length % sizeof(T) != 0) {
    throw std::runtime_error("Invalid buffer length");
  }
  res.resize(length / sizeof(T));
  auto *ptr = reinterpret_cast<char *>(res.data());
  uint32_t rem = length;
  while (rem) {
    int read = stream.readRawData(ptr, rem);
    if (read <= 0) {
      throw std::runtime_error("Unable to read buffer");
    }
    rem -= read;
  }
  return res;
}

} // namespace

namespace Kononov {

FirstRenderable::FirstRenderable(const QString &texture_file,
                                 std::shared_ptr<FirstShader> &shader)
    : m_shader_parameters(), m_shader(shader) {
  m_texture = std::make_unique<QOpenGLTexture>(QImage(texture_file).mirrored());
  m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
  m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

FirstRenderable::FirstRenderable(GLenum primitive,
                                 std::shared_ptr<FirstShader> &shader,
                                 const QString &texture_file,
                                 const QString &geometry_file)
    : FirstRenderable(texture_file, shader) {
  QFile file(geometry_file);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Unable to open file " << geometry_file;
  }
  QDataStream stream(&file);
  stream.setByteOrder(QDataStream::LittleEndian);
  auto vbo_data = readVector<Vertex>(stream);
  auto ibo_data = readVector<GLuint>(stream);
  m_mesh = std::make_unique<MeshBuffers<Vertex, GLuint>>(vbo_data, ibo_data,
                                                         primitive);
  m_mesh->setupVao(*m_shader);
}

FirstRenderable::FirstRenderable(GLenum primitive,
                                 std::shared_ptr<FirstShader> &shader,
                                 const QString &texture_file,
                                 const std::vector<Vertex> &vertices,
                                 const std::vector<GLuint> &indices)
    : FirstRenderable(texture_file, shader) {
  m_mesh = std::make_unique<MeshBuffers<Vertex, GLuint>>(vertices, indices,
                                                         primitive);
  m_mesh->setupVao(*m_shader);
}

void FirstRenderable::render(QMatrix4x4 view, QMatrix4x4 model) {
  m_texture->bind();
  m_shader->bind();

  m_shader->setMatrices(view, model);
  m_shader->setParameters(m_shader_parameters);

  m_mesh->drawElements();

  m_shader->release();
  m_texture->release();
}

const FirstShaderParameters &
FirstRenderable::getShaderParameters() const noexcept {
  return m_shader_parameters;
}

FirstShaderParameters &FirstRenderable::getShaderParameters() noexcept {
  return m_shader_parameters;
}

void FirstRenderable::setShaderParameters(
    const FirstShaderParameters &shader_parameters) {
  m_shader_parameters = shader_parameters;
}

} // namespace Kononov
