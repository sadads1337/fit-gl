#pragma once
#include "GLTexture.h"
#include <QImage>

class GLTextureLoader
{

public:

	static GLTexture load_texture(const std::string& path)
	{
		GLTexture texture;
		texture.texture_data = std::make_shared<QOpenGLTexture>(QImage(path.c_str()));
		texture.texture_data->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
		texture.texture_data->setMagnificationFilter(QOpenGLTexture::Linear);
		
		return texture;
	}
	
};