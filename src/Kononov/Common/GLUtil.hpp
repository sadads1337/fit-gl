#pragma once

#include <QOpenGLContext>
#include <QOpenGLFunctions>

namespace Kononov {

class GLUtil {
public:
  static QOpenGLContext *requireContext();
  static QOpenGLFunctions *requireFunctions();
};

} // namespace Kononov
