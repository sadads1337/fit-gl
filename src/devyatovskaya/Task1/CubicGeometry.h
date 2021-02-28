#pragma once
#include "Geometry.h"

class CubicGeometry : public Geometry {

public:
  CubicGeometry() = delete;

  explicit CubicGeometry(const GLfloat edge_len, const GLuint vertex_count)
      : Geometry{vertex_count}, edge_len_(edge_len) {
    vertex_buf_.resize(vertex_count * 3u);
    color_buf_.resize(vertex_count * 3u);
  }

protected:
  GLfloat edge_len_;
};
