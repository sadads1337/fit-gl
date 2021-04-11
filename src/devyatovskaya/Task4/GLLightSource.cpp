#include "GLLightSource.h"


GLLightSource::GLLightSource(QVector3D _position, QColor _color, const float _intensity)
	:	position{ std::move(_position) },
		color{ std::move(_color) },
		intensity{ _intensity }
{
	
}

