#pragma once
#include "globject.hpp"

#include <QColor>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

class rectFlatGridSurface final : public GLObject, protected QOpenGLFunctions {
  std::vector<QVector3D> vertices_;
  std::vector<GLushort> indices_;
  QOpenGLBuffer arrayBuf_;
  QOpenGLBuffer indexBuf_;
  QColor face_color_;
  QColor edge_color_;
  bool drawEdges_ = true;
  bool drawFaces_ = true;

public:
  rectFlatGridSurface(size_t steps, QColor const &face_color,
                      QColor const &edge_color);
  rectFlatGridSurface(rectFlatGridSurface const &,
                      QMatrix4x4 const &transformation);

  void draw(QOpenGLShaderProgram &program);
  void initialize(size_t steps);

  void setFaceColor(QColor const &color);
  void setEdgeColor(QColor const &color);

  QColor getFaceColor() const;
  QColor getEdgeColor() const;

  void transform(QMatrix4x4 const &matrix);
  rectFlatGridSurface getTransformated(QMatrix4x4 const &matrix);

private:
  void drawEdges(QOpenGLShaderProgram &program);
  void drawFaces(QOpenGLShaderProgram &program);

  void destroy();
  void load();
  void reload();
};
