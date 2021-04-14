#include <memory>
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

std::vector<std::shared_ptr<Renderable>> objects;

inline QVector3D mix(const QVector3D &a, const QVector3D &b, float k) {
  return a * k + b * (1 - k);
}

bool trace_one(const Ray &ray, RayHit &hit) {
  RayHit tmp_hit;
  float nearest = INFINITY;
  for (const auto &o : objects) {
    if (o->getHit(ray, tmp_hit)) {
      if (tmp_hit.dist < nearest) {
        hit = tmp_hit;
        nearest = tmp_hit.dist;
      }
    }
  }
  return !std::isinf(nearest);
}

bool test_light(const Ray &ray) {
  auto distance = (LIGHT_POS - ray.origin).length();
  RayHit hit;
  return !trace_one(ray, hit) || hit.dist > distance;
}

QVector3D trace(const Ray &ray, const int limit) {
  if (limit == 0) {
    return CLEAR_COLOR;
  }
  RayHit hit;
  bool inter = trace_one(ray, hit);
  if (!inter) {
    return CLEAR_COLOR;
  }
  auto ref_color =
      trace({hit.position, reflect(ray.direction, hit.normal)}, limit - 1);
  auto a = ambient(AMBIENT_STRENGTH, AMBIENT_COLOR);
  auto light_dir = (LIGHT_POS - hit.position).normalized();
  auto view_dir = -ray.direction;
  auto light_color =
      test_light({hit.position, light_dir}) ? LIGHT_COLOR : QVector3D();
  auto d = diffuse(hit.normal, light_dir, light_color);
  auto s = specular(hit.normal, light_dir, view_dir, SPECULAR_STRENGTH,
                    SPECULAR_POWER, light_color);
  auto own_color = (a + d + s) * hit.color;
  auto k = std::exp(-hit.dist / TRANSPARENCY_LENGTH);
  return mix(ref_color, mix(own_color, CLEAR_COLOR, k), hit.reflection);
}

Ray make_ray(const QVector3D &pos, const float hfov, const float vfov, int x,
             int y, int w, int h) {
  auto hsin =
      (static_cast<float>(x) / static_cast<float>(w) - 0.5F) * std::sin(hfov);
  auto vsin =
      (static_cast<float>(-y) / static_cast<float>(h) + 0.5F) * std::sin(vfov);
  return {pos, {hsin, vsin, -sqrtf(1 - sqr(hsin) - sqr(vsin))}};
}

int main() {
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

  const float hfov = 60.0F * DEG_TO_RAD;
  const float vfov = hfov * HEIGHT / WIDTH;

  // Draw big image
  QImage result(WIDTH * 2, HEIGHT * 2, QImage::Format_ARGB32);
  for (int y = 0; y < result.height(); ++y) {
    for (int x = 0; x < result.width(); ++x) {
      auto ray = make_ray(CAMERA_POS, hfov, vfov, x, y, result.width(),
                          result.height());
      QVector3D color = trace(ray, MAX_REFLECTIONS);
      result.setPixelColor(x, y,
                           QColor::fromRgbF(color.x(), color.y(), color.z()));
    }
  }

  // Shrink and save image
  result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
      .save("result.png");
  return 0;
}
