#include "SecondRenderable.hpp"

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

SecondRenderable::SecondRenderable(const QString &texture_file,
                                 std::shared_ptr<SecondShader> &shader)
    : m_shader_parameters(), m_shader(shader) {
  m_texture = std::make_unique<QOpenGLTexture>(QImage(texture_file).mirrored());
  m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
  m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
  m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

SecondRenderable::SecondRenderable(GLenum primitive,
                                 std::shared_ptr<SecondShader> &shader,
                                 const QString &texture_file,
                                 const QString &geometry_file)
    : SecondRenderable(texture_file, shader) {
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

SecondRenderable::SecondRenderable(GLenum primitive,
                                 std::shared_ptr<SecondShader> &shader,
                                 const QString &texture_file,
                                 const std::vector<Vertex> &vertices,
                                 const std::vector<GLuint> &indices)
    : SecondRenderable(texture_file, shader) {
  m_mesh = std::make_unique<MeshBuffers<Vertex, GLuint>>(vertices, indices,
                                                         primitive);
  m_mesh->setupVao(*m_shader);
}

void SecondRenderable::render(Camera camera, QMatrix4x4 model_matrix) {
  m_texture->bind();
  m_shader->bind();

  m_shader->setParameters(m_shader_parameters);
  m_shader->prepare(camera, model_matrix);

  m_mesh->drawElements();

  m_shader->release();
  m_texture->release();
}

const SecondShaderParameters &
SecondRenderable::getShaderParameters() const noexcept {
  return m_shader_parameters;
}

SecondShaderParameters &SecondRenderable::getShaderParameters() noexcept {
  return m_shader_parameters;
}

void SecondRenderable::setShaderParameters(
    const SecondShaderParameters &shader_parameters) {
  m_shader_parameters = shader_parameters;
}

} // namespace Kononov
