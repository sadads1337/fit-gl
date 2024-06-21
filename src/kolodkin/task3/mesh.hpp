#pragma once
#include "vertex.hpp"

#include <QOpenGLFunctions>
#include <vector>

struct Mesh {
  using vertexType = Vertex;
  using indexType = GLuint;
  inline static constexpr GLenum IndexTypeVal = GL_UNSIGNED_INT;

  std::vector<vertexType> vertices{};
  std::vector<indexType> indices{};

  Mesh() = default;
  Mesh(std::vector<vertexType> _vertices, std::vector<indexType> _indices)
      : vertices(std::move(_vertices)), indices(std::move(_indices)) {}
};
