#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

#include <QDataStream>
#include <QFile>
#include <QString>

#include "Mesh.hpp"

namespace Kononov {

class MeshLoader {
private:
  template <typename T> static std::vector<T> readVector(QDataStream &stream) {
    std::vector<T> res;
    uint32_t length = 0;
    stream >> length;
    if (length % sizeof(T) != 0) {
      throw std::runtime_error("Invalid buffer length");
    }
    res.resize(length / sizeof(T));
    auto *ptr = reinterpret_cast<char *>(res.data());
    uint32_t rem = length;
    while (rem) {
      int read = stream.readRawData(ptr, rem);
      if (read <= 0) {
        throw std::runtime_error("Unable to read buffer");
      }
      rem -= read;
    }
    return res;
  }

public:
  template <typename TVertex, typename TIndex>
  static std::unique_ptr<GenericMesh<TVertex, TIndex>>
  load(const QString &filename, GLenum primitive) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << "Unable to open file " << filename;
    }
    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);
    auto vbo_data = readVector<TVertex>(stream);
    auto ibo_data = readVector<TIndex>(stream);
    return std::make_unique<GenericMesh<TVertex, TIndex>>(vbo_data, ibo_data,
                                                          primitive);
  }
};

} // namespace Kononov
