#pragma once
#include "Ray.h"

class Interface {
public:
  Interface() = default;
  Interface(const Interface &) = default;
  Interface(Interface &&) noexcept = default;
  virtual ~Interface() = default;
  Interface &operator=(const Interface &) = default;
  Interface &operator=(Interface &&) noexcept = default;

  virtual bool ray_intersect(const Ray &ray, float &t0) const = 0;
};
