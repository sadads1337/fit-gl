#pragma once

#include <memory>

#include <Mesh.hpp>
#include <Vertex.hpp>

namespace Kononov {

class UVSphere {
public:
  static std::unique_ptr<TypedMesh<TBNVertex>> generate(unsigned int lat_num,
                                                        unsigned int long_num);

  static std::shared_ptr<TypedMesh<TBNVertex>>
  generateShared(unsigned int lat_num, unsigned int long_num);
};

} // namespace Kononov
