#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>

namespace Kononov {

template <typename T> constexpr GLenum glTypeToEnum();
template <> constexpr GLenum glTypeToEnum<GLfloat>() { return GL_FLOAT; }
template <> constexpr GLenum glTypeToEnum<GLint>() { return GL_INT; }
template <> constexpr GLenum glTypeToEnum<GLuint>() { return GL_UNSIGNED_INT; }
template <> constexpr GLenum glTypeToEnum<GLshort>() { return GL_SHORT; }
template <> constexpr GLenum glTypeToEnum<GLushort>() {
  return GL_UNSIGNED_SHORT;
}

class GLUtil {
public:
  static QOpenGLContext *requireContext();
  static QOpenGLFunctions *requireFunctions();
};

} // namespace Kononov
