#include "GLMeshGenerator.h"

void GLMeshGenerator::init_tangent_bitangent_vectors(
    std::vector<GLVertex> &vertices, std::vector<unsigned> &indices) const {
  for (auto i = 0u; i < indices.size(); i += 3) {
    auto &vertex0 = vertices[indices[0u + i]];
    auto &vertex1 = vertices[indices[1u + i]];
    auto &vertex2 = vertices[indices[2u + i]];

    const auto Edge1 = vertex1.coordinate - vertex0.coordinate;
    const auto Edge2 = vertex2.coordinate - vertex0.coordinate;

    const auto DeltaU1 = vertex1.texture.x() - vertex0.texture.x();
    const auto DeltaV1 = vertex1.texture.y() - vertex0.texture.y();
    const auto DeltaU2 = vertex2.texture.x() - vertex0.texture.x();
    const auto DeltaV2 = vertex2.texture.y() - vertex0.texture.y();

    const auto f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

    QVector3D Tangent, Bitangent;

    Tangent.setX(f * (DeltaV2 * Edge1.x() - DeltaV1 * Edge2.x()));
    Tangent.setY(f * (DeltaV2 * Edge1.y() - DeltaV1 * Edge2.y()));
    Tangent.setZ(f * (DeltaV2 * Edge1.z() - DeltaV1 * Edge2.z()));

    Bitangent.setX(f * (-DeltaU2 * Edge1.x() + DeltaU1 * Edge2.x()));
    Bitangent.setY(f * (-DeltaU2 * Edge1.y() + DeltaU1 * Edge2.y()));
    Bitangent.setZ(f * (-DeltaU2 * Edge1.z() + DeltaU1 * Edge2.z()));

    vertex0.tangent = Tangent.normalized();
    vertex1.tangent = Tangent.normalized();
    vertex2.tangent = Tangent.normalized();

    vertex0.bitangent = Bitangent.normalized();
    vertex1.bitangent = Bitangent.normalized();
    vertex2.bitangent = Bitangent.normalized();
  }
}
