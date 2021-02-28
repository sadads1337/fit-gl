#include "GLUtil.hpp"

#include <stdexcept>

namespace Kononov::GL {

QOpenGLContext *requireContext() {
  QOpenGLContext *context = QOpenGLContext::currentContext();
  if (context == nullptr) {
    throw std::runtime_error("No current OpenGL context");
  }
  return context;
}

QOpenGLFunctions *requireFunctions() { return requireContext()->functions(); }

} // namespace Kononov::GL
