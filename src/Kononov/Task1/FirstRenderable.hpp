#pragma once

#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QString>

#include "FirstShader.hpp"

namespace Kononov {

class FirstRenderable {
private:
  GLenum m_primitive;
  FirstShaderParameters m_shader_parameters;
  std::shared_ptr<FirstShader> m_shader;
  std::unique_ptr<QOpenGLTexture> m_texture;
  std::unique_ptr<QOpenGLBuffer> m_vbo;
  std::unique_ptr<QOpenGLBuffer> m_ibo;
  std::unique_ptr<QOpenGLVertexArrayObject> m_vao;

  static std::unique_ptr<QOpenGLBuffer> readGLBuffer(QDataStream &stream,
                                                     QOpenGLBuffer::Type type);

  static std::unique_ptr<QOpenGLBuffer>
  bufferFromData(const char *data, int size, QOpenGLBuffer::Type type);

  void initVao();

  FirstRenderable(GLenum primitive, const QString &texture_file,
                   std::shared_ptr<FirstShader> &shader);

public:
  FirstRenderable(GLenum primitive, std::shared_ptr<FirstShader> &shader,
                   const QString &texture_file, const QString &geometry_file);
  FirstRenderable(GLenum primitive, std::shared_ptr<FirstShader> &shader,
                   const QString &texture_file, const char *vbo_data,
                   int vbo_size, const char *ibo_data, int ibo_size);

  void render(QMatrix4x4 view, QMatrix4x4 model);

  [[nodiscard]] const FirstShaderParameters &getShaderParameters() const;
  [[nodiscard]] FirstShaderParameters &getShaderParameters();
  void setShaderParameters(const FirstShaderParameters &shader_parameters);
};

} // namespace Kononov
