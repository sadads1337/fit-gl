#pragma once
#include "globject.hpp"
#include "rectflatgridsurface.hpp"

#include <QOpenGLBuffer>
#include <QVector3D>
#include <vector>

class Cube : public GLObject {
  std::vector<rectFlatGridSurface> faces_;

  void scale(QVector3D const &scale);

public:
  Cube(size_t steps, QVector3D const &size, QColor const &face_color,
       QColor const &edges_color = Qt::GlobalColor::white);

  void draw(QOpenGLShaderProgram &program) override;
  void initialize(size_t steps, QColor const &face_color,
                  QColor const &edge_color, QVector3D const &size);
  void setFaceColor(QColor const &color, int face = -1);
  void setEdgeColor(QColor const &color, int face = -1);

  QColor getFaceColor(int face);
  QColor getEdgeColor(int face);
};
