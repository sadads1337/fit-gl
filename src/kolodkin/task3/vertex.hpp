#pragma once
#include <QVector3D>
#include <QVector4D>
//#include <QColor>

struct Vertex {
  QVector3D position;
  inline static constexpr size_t positionTupleSize =
      sizeof(position) / sizeof(float);

  QVector3D normal;
  inline static constexpr size_t normalTupleSize =
      sizeof(normal) / sizeof(float);

  //    QVector4D color;
  //    inline static constexpr size_t colorTupleSize = sizeof(color) /
  //    sizeof(float);

  Vertex(QVector3D const &pos, QVector3D const &norm)
      : position(pos), normal(norm) {}
};
