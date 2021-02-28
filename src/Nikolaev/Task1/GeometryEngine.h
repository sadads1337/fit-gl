//
// Created by andre on 21.02.2021.
//

#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>

class GeometryEngine : protected QOpenGLFunctions {
public:
  GeometryEngine();
  virtual ~GeometryEngine();

  void drawCubeGeometry(QOpenGLShaderProgram *program);

  void setColor(QVector3D RGBcolors);

private:
  void initCubeGeometry();

  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;
};
