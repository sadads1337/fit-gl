#include "GLUtil.hpp"

namespace Kononov {

QOpenGLContext *GLUtil::requireContext() {
  QOpenGLContext *context = QOpenGLContext::currentContext();
  if (context == nullptr) {
    throw std::runtime_error("No current OpenGL context");
  }
  return context;
}

QOpenGLFunctions *GLUtil::requireFunctions() {
  return requireContext()->functions();
}

} // namespace Kononov