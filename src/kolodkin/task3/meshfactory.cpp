#include "meshfactory.hpp"
#include <QMatrix4x4>

std::shared_ptr<Mesh> MeshFactory::makeCube(const QVector3D &size,
                                            std::size_t grid_steps) {
  auto pCube = std::make_shared<Mesh>();
  pCube->vertices.reserve(6 * (grid_steps + 1) * (grid_steps + 1));
  pCube->indices.reserve(6 * 6 * grid_steps * grid_steps);
  float step = 1.f / grid_steps;
  QVector3D const baseNormal{0.f, 0.f, 1.f};

  for (size_t j = 0; j < grid_steps + 1; ++j) {
    for (size_t i = 0; i < grid_steps + 1; ++i) {
      pCube->vertices.emplace_back(
          QVector3D(-0.5f + step * i, -0.5f + step * j, 0.5f), baseNormal);
    }
  }
  for (size_t j = 0; j < grid_steps; ++j) {
    for (size_t i = 0; i < grid_steps; ++i) {
      auto k = i + (j + 1) * (grid_steps + 1);
      auto p = i + j * (grid_steps + 1);
      pCube->indices.push_back(k);
      pCube->indices.push_back(p);
      pCube->indices.push_back(p + 1);

      pCube->indices.push_back(p + 1);
      pCube->indices.push_back(k + 1);
      pCube->indices.push_back(k);
    }
  }
  auto vertexCount = pCube->vertices.size();
  auto indexCount = pCube->indices.size();
  size_t maxIndex = 0;

  QMatrix4x4 rotation;
  for (size_t n = 0; n < 3; ++n) {
    rotation.rotate(90.f, 0.f, 1.f);
    auto normal = rotation * baseNormal;
    maxIndex = pCube->vertices.size();

    for (size_t i = 0; i < vertexCount; ++i) {
      pCube->vertices.emplace_back(rotation * pCube->vertices[i].position,
                                   normal);
    }
    for (size_t i = 0; i < indexCount; ++i) {
      pCube->indices.push_back(pCube->indices[i] + maxIndex);
    }
  }
  rotation.setToIdentity();
  rotation.rotate(90.f, 1.f, 0.f);
  auto normal = rotation * baseNormal;
  maxIndex = pCube->vertices.size();

  for (size_t i = 0; i < vertexCount; ++i) {
    pCube->vertices.emplace_back(rotation * pCube->vertices[i].position,
                                 normal);
  }
  for (size_t i = 0; i < indexCount; ++i) {
    pCube->indices.push_back(pCube->indices[i] + maxIndex);
  }

  rotation.rotate(180.f, 1.f, 0.f);
  normal = rotation * baseNormal;
  maxIndex = pCube->vertices.size();

  for (size_t i = 0; i < vertexCount; ++i) {
    pCube->vertices.emplace_back(rotation * pCube->vertices[i].position,
                                 normal);
  }
  for (size_t i = 0; i < indexCount; ++i) {
    pCube->indices.push_back(pCube->indices[i] + maxIndex);
  }

  // Resize unit cube to given sized
  for (auto &vertex : pCube->vertices) {
    vertex.position *= size;
  }

  return pCube;
}
