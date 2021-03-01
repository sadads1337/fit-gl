#include "TextureLoader.hpp"
namespace Kononov {

std::unique_ptr<QOpenGLTexture> TextureLoader::load(const QString &filename) {
  auto texture = std::make_unique<QOpenGLTexture>(QImage(filename).mirrored());
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
  return texture;
}

} // namespace Kononov
