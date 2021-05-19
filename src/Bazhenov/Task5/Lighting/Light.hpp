#ifndef FIT_GL_LIGHT_HPP
#define FIT_GL_LIGHT_HPP

#include "Ray.hpp"

namespace Bazhenov {

QVector3D ambient(float strength, QVector3D light_color);

QVector3D diffuse(QVector3D normal, QVector3D light_dir, QVector3D light_color);

QVector3D specular(QVector3D normal, QVector3D light_dir, QVector3D view_dir,
                   float strength, float power, QVector3D light_color);

}

#endif // FIT_GL_LIGHT_HPP
