#pragma once

#include <vector>

#include <QOpenGLContext>

#include "Vertex.hpp"

namespace Kononov {

extern const std::vector<Kononov::RegularVertex> cubeVertices;
extern const std::vector<GLuint> cubeStripeIndices;
extern const std::vector<GLuint> cubeTrianglesIndices;

} // namespace Kononov