#pragma once
#include "GLMesh.h"
#include <QColor>

class GLMeshGenerator {
public:
  GLMeshGenerator() = default;

  virtual GLMesh generate(const QColor &color) const = 0;
  virtual ~GLMeshGenerator() = default;

protected:
  void init_tangent_bitangent_vectors(std::vector<GLVertex> &vertices,
                                      std::vector<unsigned> &indices) const;

  virtual void init_vertices(std::vector<GLVertex> &vertices,
                             const QColor &color) const = 0;
  virtual void init_indices(std::vector<unsigned> &indices) const = 0;
};