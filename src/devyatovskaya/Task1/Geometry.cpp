#include "Geometry.h"

std::vector<GLfloat> &Geometry::ColorArray() { return color_buf_; }

const std::vector<GLfloat> &Geometry::ColorArray() const { return color_buf_; }

std::size_t Geometry::VertexCount() const { return vertex_count_; }
