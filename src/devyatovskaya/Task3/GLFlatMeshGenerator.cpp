#include "GLFlatMeshGenerator.h"

GLFlatMeshGenerator::GLFlatMeshGenerator(const float edge_len,
                                         const unsigned steps_count)
    : edge_len_{edge_len}, step_count_{steps_count} {}

GLMesh GLFlatMeshGenerator::generate(const QColor &color) const {
  GLMesh mesh{};

  mesh.vertices.reserve((step_count_ + 1u) * (step_count_ + 1u));
  mesh.indices.reserve(6u * step_count_ * step_count_);

  init_vertices(mesh.vertices, color);
  init_indices(mesh.indices);
  init_tangent_bitangent_vectors(mesh.vertices, mesh.indices);

  return mesh;
}

unsigned GLFlatMeshGenerator::step_count() const { return step_count_; }

void GLFlatMeshGenerator::init_vertices(std::vector<GLVertex> &vertices,
                                        const QColor &color) const {
  const auto normalized_step = edge_len_ / static_cast<float>(step_count_);
  GLVertex vertex{};

  for (std::size_t j = 0; j < step_count_ + 1; ++j) {
    for (std::size_t i = 0; i < step_count_ + 1; ++i) {
      vertex.coordinate.setX(-edge_len_ / 2.f +
                             normalized_step * static_cast<float>(i));
      vertex.coordinate.setY(-edge_len_ / 2.f +
                             normalized_step * static_cast<float>(j));
      vertex.coordinate.setZ(edge_len_ / 2.f);

      vertex.normal.setX(0.0f);
      vertex.normal.setY(0.0f);
      vertex.normal.setZ(1.0f);

      vertex.color.setX(static_cast<float>(color.redF()));
      vertex.color.setY(static_cast<float>(color.greenF()));
      vertex.color.setZ(static_cast<float>(color.blueF()));

      vertex.texture = {static_cast<float>(j) / normalized_step,
                        static_cast<float>(i) / normalized_step};

      vertices.emplace_back(vertex);
    }
  }
}

void GLFlatMeshGenerator::init_indices(std::vector<unsigned> &indices) const {
  for (unsigned j = 0; j < step_count_; ++j) {

    for (unsigned i = 0; i < step_count_; ++i) {

      auto k = i + (j + 1) * (step_count_ + 1);
      auto p = i + j * (step_count_ + 1);
      indices.push_back(k);
      indices.push_back(p);
      indices.push_back(p + 1);

      indices.push_back(p + 1);
      indices.push_back(k + 1);
      indices.push_back(k);
    }
  }
}
