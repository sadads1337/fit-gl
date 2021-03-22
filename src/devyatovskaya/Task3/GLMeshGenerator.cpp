#include "GLMeshGenerator.h"

void GLMeshGenerator::init_tangent_bitangent_vectors(std::vector<GLVertex>& vertices, std::vector<unsigned>& indices) const
{
    for (auto i = 0u; i < indices.size(); i += 3) {
        auto& vertex0 = vertices[indices[0u + i]];
        auto& vertex1 = vertices[indices[1u + i]];
        auto& vertex2 = vertices[indices[2u + i]];

        auto& v0 = vertex0.coordinate;
        auto& v1 = vertex1.coordinate;
        auto& v2 = vertex2.coordinate;

        auto& uv0 = vertex0.texture;
        auto& uv1 = vertex1.texture;
        auto& uv2 = vertex2.texture;

        const auto deltaPos1 = v1 - v0;
        const auto deltaPos2 = v2 - v0;

        const auto deltaUV1 = uv1 - uv0;
        const auto deltaUV2 = uv2 - uv0;

        const auto r = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
        const auto tangent = (deltaPos1 * deltaUV2.y() - deltaPos2 * deltaUV1.y()) * r;
        const auto bitangent = (deltaPos2 * deltaUV1.x() - deltaPos1 * deltaUV2.x()) * r;


        vertex0.tangent = tangent.normalized();
        vertex1.tangent = tangent.normalized();
        vertex2.tangent = tangent.normalized();

        vertex0.bitangent = bitangent.normalized();
        vertex1.bitangent = bitangent.normalized();
        vertex2.bitangent = bitangent.normalized();

    }
}
