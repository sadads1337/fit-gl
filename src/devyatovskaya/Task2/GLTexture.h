#pragma once
#include <string>
#include <QOpenGLTexture>


struct GLTexture
{
    std::string type;
    std::string path;
	std::shared_ptr<QOpenGLTexture> texture_data;
};