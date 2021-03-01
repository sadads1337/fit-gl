#pragma once

#include <memory>

#include <QOpenGLTexture>

namespace Kononov {

class TextureLoader {
public:
  static std::unique_ptr<QOpenGLTexture> load(const QString &filename);
};

} // namespace Kononov
