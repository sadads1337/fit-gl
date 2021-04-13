#include "UVSphere.hpp"

#include <cmath>

namespace {
constexpr float pi = 3.141592F;
}

namespace Kononov {

std::unique_ptr<TypedMesh<TBNVertex>>
UVSphere::generate(unsigned int lat_num, unsigned int long_num) {
  std::vector<TBNVertex> vertices;
  vertices.reserve(lat_num * (long_num + 1));
  std::vector<GLuint> indices;
  for (unsigned int i = 0; i <= lat_num; ++i) {
    for (unsigned int j = 0; j <= long_num; ++j) {
      const float u = static_cast<float>(j) / static_cast<float>(long_num);
      const float v = static_cast<float>(i) / static_cast<float>(lat_num);
      const auto phi = u * pi * 2;
      const auto theta = v * pi;
      QVector3D pos{std::sin(phi) * std::sin(theta), std::cos(theta),
                    std::cos(phi) * std::sin(theta)};
      QVector2D uv{u, 1 - v};
      QVector3D norm = pos.normalized();
      QVector3D tangent{-std::cos(phi) * std::cos(theta), std::sin(theta),
                        -std::sin(phi) * std::cos(theta)};
      QVector3D bitangent = QVector3D::crossProduct(tangent, norm);
      vertices.push_back({pos, uv, tangent, bitangent, norm});
      if (i > 0 && j > 0) {
        auto step = long_num + 1;
        indices.push_back(i * step + j);
        indices.push_back((i - 1) * step + (j - 1));
        indices.push_back(i * step + (j - 1));

        indices.push_back(i * step + j);
        indices.push_back((i - 1) * step + j);
        indices.push_back((i - 1) * step + (j - 1));
      }
    }
  }
  return std::make_unique<GenericMesh<TBNVertex, GLuint>>(vertices, indices,
                                                          GL_TRIANGLES);
}

std::shared_ptr<TypedMesh<TBNVertex>>
UVSphere::generateShared(unsigned int lat_num, unsigned int long_num) {
  return generate(lat_num, long_num);
}

} // namespace Kononov
