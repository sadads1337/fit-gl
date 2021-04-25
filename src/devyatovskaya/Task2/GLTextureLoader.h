#pragma once
#include "GLTexture.h"
#include <QImage>

class GLTextureLoader {

public:
  static void load_texture(GLMaterial &material,
                           const std::string &texture_path,
                           const std::string &normal_path) {
    GLTexture texture;
    texture.texture_data =
        std::make_shared<QOpenGLTexture>(QImage(texture_path.c_str()));
    texture.texture_data->setMinificationFilter(
        QOpenGLTexture::LinearMipMapLinear);
    texture.texture_data->boundTextureId(
        QOpenGLTexture::BindingTarget2DMultisample);
    texture.texture_data->setMagnificationFilter(QOpenGLTexture::Linear);
    GLTexture normal;
    normal.texture_data =
        std::make_shared<QOpenGLTexture>(QImage(normal_path.c_str()));
    normal.texture_data->setMinificationFilter(
        QOpenGLTexture::LinearMipMapLinear);
    texture.texture_data->boundTextureId(
        QOpenGLTexture::BindingTarget2DMultisample);
    normal.texture_data->setMagnificationFilter(QOpenGLTexture::Linear);

    material.texture.push_back(texture);
    material.normals.push_back(normal);
  }
};