#pragma once
#ifndef FIT_GL_PLANE_H
#define FIT_GL_PLANE_H
#include "Hittable.h"
#include "QImage"

class Plane : public Hittable {
public:
  Plane(QVector3D p, QVector3D n) : position(p), normal(n) {};

  virtual bool hit(const Ray& r,  hit_record& rec) const override;

public:
  QVector3D position;
  QVector3D normal;

};


#endif // FIT_GL_PLANE_H
