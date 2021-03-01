#pragma once

#include <QVector2D>
#include <QVector3D>

namespace Kononov {

template <typename VertexType, typename VertexInterface> class VertexMapper;

class BaseVertexInterface {
public:
  [[nodiscard]] virtual int getStride() const = 0;
};

struct SimpleVertex {
  QVector3D position;

  class Interface : public BaseVertexInterface {
  public:
    [[nodiscard]] virtual int getPositionOffset() const = 0;
  };
};

template <>
class VertexMapper<SimpleVertex, SimpleVertex::Interface>
    : public SimpleVertex::Interface {
public:
  [[nodiscard]] int getStride() const override { return sizeof(SimpleVertex); }
  [[nodiscard]] int getPositionOffset() const override {
    return offsetof(SimpleVertex, position);
  }
};

struct RegularVertex {
  QVector3D position;
  QVector3D normal;
  QVector2D uv;

  class Interface : public SimpleVertex::Interface {
  public:
    [[nodiscard]] virtual int getNormalOffset() const = 0;
    [[nodiscard]] virtual int getUVOffset() const = 0;
  };
};

template <>
class VertexMapper<RegularVertex, RegularVertex::Interface>
    : public RegularVertex::Interface {
public:
  [[nodiscard]] int getStride() const override { return sizeof(RegularVertex); }
  [[nodiscard]] int getPositionOffset() const override {
    return offsetof(RegularVertex, position);
  }
  [[nodiscard]] int getNormalOffset() const override {
    return offsetof(RegularVertex, normal);
  }
  [[nodiscard]] int getUVOffset() const override {
    return offsetof(RegularVertex, uv);
  }
};

template <>
class VertexMapper<RegularVertex, SimpleVertex::Interface>
    : public VertexMapper<RegularVertex, RegularVertex::Interface> {};

} // namespace Kononov
