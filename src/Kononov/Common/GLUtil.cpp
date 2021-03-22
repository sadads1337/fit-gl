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

QOpenGLFunctions_4_0_Core *requireFunctions40core() {
  return requireContext()->versionFunctions<QOpenGLFunctions_4_0_Core>();
}

} // namespace Kononov::GL
