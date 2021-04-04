#pragma once

#include <QMatrix4x4>
#include <QVector3D>

class cameraView {
  QVector3D position_;
  QVector3D center_;
  QVector3D up_;

public:
  QMatrix4x4 getViewMatrix();
};
