#include <memory>
#include <optional>
#include <vector>

#include <QImage>
#include <QPainter>

#include "Colors.hpp"
#include "Geometry.hpp"
#include "Ground.hpp"
#include "Lightning.hpp"
#include "Renderable.hpp"
#include "Sphere.hpp"
#include "Types.hpp"

using namespace Kononov;

constexpr int WIDTH = 640;
constexpr int HEIGHT = 480;
constexpr float PI = 3.141592F;
constexpr float DEG_TO_RAD = PI / 180.0F;

constexpr int MAX_REFLECTIONS = 5;
constexpr float TRANSPARENCY_LENGTH = 40.0F;
constexpr QVector3D CLEAR_COLOR{0.0F, 0.25F, 0.5F};

constexpr float AMBIENT_STRENGTH = 0.3F;
constexpr QVector3D AMBIENT_COLOR{1.0F, 1.0F, 1.0F};
constexpr float SPECULAR_STRENGTH = 1.5F;
constexpr int SPECULAR_POWER = 32;

constexpr QVector3D LIGHT_COLOR{1.0F, 1.0F, 1.0F};
constexpr QVector3D LIGHT_POS{2.0F, 2.0F, 2.0F};
constexpr QVector3D CAMERA_POS{0.0F, 1.1F, 7.0F};

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
  const auto distance = (LIGHT_POS - ray.origin).length();
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
  const auto light_dir = (LIGHT_POS - hit.position).normalized();
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

  // Generate five yellow spheres with increasing reflectivity
  for (int i = 0; i < 5; ++i) {
    objects.push_back(std::make_shared<Sphere>(
        YELLOW, QVector3D((i - 2.0F) * 1.1F, 0.5F, 0), 0.5F, i / 4.0F));
  }
  // Big red sphere
  objects.push_back(
      std::make_shared<Sphere>(RED, QVector3D(0, 2.5F, 0), 1.0F, 0.5F));
  // Small green sphere
  objects.push_back(
      std::make_shared<Sphere>(GREEN, QVector3D(0.5F, 0.1F, 3.5F), 0.1F, 0.2F));
  // Ground
  objects.push_back(
      std::make_shared<Ground>(WHITE_REFLECTIVITY, BLACK_REFLECTIVITY));

  constexpr auto hfov = 60.0F * DEG_TO_RAD;
  constexpr auto vfov = hfov * HEIGHT / WIDTH;

  // Draw big image
  QImage result(WIDTH * 2, HEIGHT * 2, QImage::Format_ARGB32);
  for (int y = 0; y < result.height(); ++y) {
    for (int x = 0; x < result.width(); ++x) {
      const auto ray = make_ray(CAMERA_POS, hfov, vfov, x, y, result.width(),
                                result.height());
      QVector3D color = trace(objects, ray, MAX_REFLECTIONS);
      result.setPixelColor(x, y,
                           QColor::fromRgbF(color.x(), color.y(), color.z()));
    }
  }

  // Shrink and save image
  result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
      .save("result.png");
  return 0;
}
