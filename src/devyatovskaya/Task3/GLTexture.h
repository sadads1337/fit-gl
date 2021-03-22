#pragma once
#include <string>
#include <QOpenGLTexture>
#include <memory>


struct GLTexture
{
    // std::string type;
    // std::string path;
	std::shared_ptr<QOpenGLTexture> texture_data{ nullptr };
	std::shared_ptr<QOpenGLTexture> normal_map_data{ nullptr };
};
