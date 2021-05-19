#include <memory>
#include <optional>
#include <vector>

#include <QImage>
#include <QPainter>

#include "Lighting/Colors.hpp"
#include "Geometry/Geometry.hpp"
#include "Lighting/Ray.hpp"
#include "Lighting/Light.hpp"
#include "Renderable/Renderable.hpp"
#include "Renderable/Plane.hpp"
#include "Renderable/Sphere.hpp"

using namespace Bazhenov;

constexpr int IMG_WIDTH = 640;
constexpr int IMG_HEIGHT = 480;

constexpr float PI = 3.1415926F;
constexpr float DEG_TO_RAD = PI / 180.0F;

constexpr int MAX_REFLECTIONS = 5;
constexpr float TRANSPARENCY_LENGTH = 40.0F;
constexpr QVector3D CLEAR_COLOR{0.25F, 0.25F, 0.375F};

constexpr float AMBIENT_STRENGTH = 0.2F;
constexpr QVector3D AMBIENT_COLOR{1.0F, 1.0F, 1.0F};
constexpr float SPECULAR_STRENGTH = 1.0F;
constexpr int SPECULAR_POWER = 32;

constexpr QVector3D LIGHT_COLOR{1.0F, 1.0F, 1.0F};
constexpr QVector3D LIGHT_POSITION{6.5F, 2.0F, 2.5F};

constexpr QVector3D CAMERA_POSITION{0.0F, 2.0F, 8.0F};

constexpr float WHITE_REFLECTIVITY = 0.0F;
constexpr float BLACK_REFLECTIVITY = 0.8F;

inline QVector3D mix(const QVector3D &a, const QVector3D &b, const float k) {
  return a * k + b * (1 - k);
}

std::optional<RayHit>
trace_one(const std::vector<std::shared_ptr<Renderable>> &objects,
          const Ray &ray) {
  RayHit res;
  float nearest = INFINITY;
  for (const auto &o : objects) {
    const auto hit = o->getHit(ray);
    if (hit.has_value()) {
      const auto &val = hit.value();
      if (val.dist < nearest) {
        nearest = val.dist;
        res = val;
      }
    }
  }
  if (std::isinf(nearest)) {
    return std::nullopt;
  }
  return res;
}

bool test_light(const std::vector<std::shared_ptr<Renderable>> &objects,
                const Ray &ray) {
  const auto distance = (LIGHT_POSITION - ray.origin).length();
  const auto hit = trace_one(objects, ray);
  return !hit.has_value() || hit.value().dist > distance;
}

QVector3D trace(const std::vector<std::shared_ptr<Renderable>> &objects,
                const Ray &ray, const int limit) {
  if (limit == 0) {
    return CLEAR_COLOR;
  }
  const auto hit_opt = trace_one(objects, ray);
  if (!hit_opt.has_value()) {
    return CLEAR_COLOR;
  }
  const auto hit = hit_opt.value();

  const auto ref_color = trace(
      objects, {hit.position, reflect(ray.direction, hit.normal)}, limit - 1);
  const auto a = ambient(AMBIENT_STRENGTH, AMBIENT_COLOR);
  const auto light_dir = (LIGHT_POSITION - hit.position).normalized();
  const auto view_dir = -ray.direction;
  const auto light_color = test_light(objects, {hit.position, light_dir})
                           ? LIGHT_COLOR
                           : QVector3D();
  const auto d = diffuse(hit.normal, light_dir, light_color);
  const auto s = specular(hit.normal, light_dir, view_dir, SPECULAR_STRENGTH,
                          SPECULAR_POWER, light_color);
  const auto own_color = (a + d + s) * hit.color;
  const auto k = std::exp(-hit.dist / TRANSPARENCY_LENGTH);
  return mix(ref_color, mix(own_color, CLEAR_COLOR, k), hit.reflection);
}

Ray make_ray(const QVector3D &pos, const float hfov, const float vfov,
             const int x, const int y, const int w, const int h) {
  const auto hsin =
      (static_cast<float>(x) / static_cast<float>(w) - 0.5F) * std::sin(hfov);
  const auto vsin =
      (static_cast<float>(-y) / static_cast<float>(h) + 0.5F) * std::sin(vfov);
  return {pos, {hsin, vsin, -sqrtf(1 - sqr(hsin) - sqr(vsin))}};
}

int main() {
  std::vector<std::shared_ptr<Renderable>> objects;

  objects.push_back(std::make_shared<Sphere>(PURPLE, QVector3D{-1.5F, 1.0F, 0.0F}, 1.0F, 0.0F));
  objects.push_back(std::make_shared<Sphere>(GREEN, QVector3D{2.5F, 1.0F, 0.0F}, 1.0F, 0.85F));
  objects.push_back(std::make_shared<Sphere>(GREEN, QVector3D{-1.0F, 2.0F, -8.0F}, 0.3F, 0.4F));
  objects.push_back(std::make_shared<Sphere>(WHITE, QVector3D{-1.0F, 0.5F, 0.8F}, 0.5F, 0.4F));
  objects.push_back(std::make_shared<Plane>(WHITE_REFLECTIVITY, BLACK_REFLECTIVITY));
  objects.push_back(std::make_shared<Plane>(WHITE_REFLECTIVITY, BLACK_REFLECTIVITY,
                                            QVector3D{0.0F, 4.0F, 0.0F},
                                            QVector3D{0.0F, -1.0F, 0.0F}));
  objects.push_back(std::make_shared<Plane>(WHITE_REFLECTIVITY, BLACK_REFLECTIVITY,
                                            QVector3D{-4.0F, 4.0F, 0.0F},
                                            QVector3D{1.0F, -1.0F, 0.0F}));

  constexpr auto hfov = 60.0F * DEG_TO_RAD;
  constexpr auto vfov = hfov * IMG_HEIGHT / IMG_WIDTH;
  
  QImage result(IMG_WIDTH * 2, IMG_HEIGHT * 2, QImage::Format_ARGB32);
  for (int y = 0; y < result.height(); ++y) {
    for (int x = 0; x < result.width(); ++x) {
      const auto ray = make_ray(CAMERA_POSITION, hfov, vfov, x, y, result.width(), result.height());
      QVector3D color = trace(objects, ray, MAX_REFLECTIONS);
      result.setPixelColor(x, y, QColor::fromRgbF(color.x(), color.y(), color.z()));
    }
  }
  
  result.scaled(IMG_WIDTH, IMG_HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
    .save("result.png");
  
  return 0;
}