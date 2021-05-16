#include "Light.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QImage>

constexpr float PI = 3.141592f;
constexpr float FOV = PI / 3; // field of view angle
auto WIDTH = 1024;
auto HEIGHT = 720;
constexpr auto REFLECTION_DEPTH = 4;
constexpr QVector3D BACKGROUND_COLOR = QVector3D(0.9f, 0.9f, 0.9f);
constexpr QVector3D LIGHT_COLOR{1.0f, 1.0f, 1.0f};

inline QVector3D mix(const QVector3D &a, const QVector3D &b, const float k) {
  return a * k + b * (1 - k);
}

QVector3D reflect(const QVector3D &incident, const QVector3D &normal) {
  return incident - 2.f * normal * (QVector3D::dotProduct(incident, normal));
}

// Snell's law
QVector3D refract(const QVector3D &incident, const QVector3D &normal, const float n_1, const float n_2 = 1.f) {
  auto cos_1 = -std::max(-1.f, std::min(1.f, QVector3D::dotProduct(incident, normal)));
  if (cos_1 < 0.f)
    return refract(incident, -normal, n_2, n_1);
  auto ratio = n_2 / n_1;
  auto cos_2 = sqrtf(1 - ratio * ratio * (1 - cos_1 * cos_1));
  return ratio * incident + (ratio * cos_1 - cos_2) * normal;
}

bool scene_intersect(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Plane> &planes, QVector3D &hit, QVector3D &normal, Material &material) {
  auto spheres_dist = std::numeric_limits<float>::max();
  for (size_t i = 0; i < spheres.size(); i++) {
    auto dist_i = std::numeric_limits<float>::max();
    if (spheres[i].ray_intersect(ray, dist_i) && dist_i < spheres_dist) {
      spheres_dist = dist_i;
      hit = ray.origin + ray.direction * dist_i;
      normal = (hit - spheres[i].center).normalized();
      material = spheres[i].material;
    }
  }

  auto checkerboard_dist = std::numeric_limits<float>::max();
  for (size_t i = 0; i < planes.size(); i++) {
    auto dist_i = std::numeric_limits<float>::max();
    if (planes[i].ray_intersect(ray, dist_i) && dist_i < spheres_dist) {
      checkerboard_dist = dist_i;
      hit = ray.origin + ray.direction * dist_i;
      normal = planes[i].normal;
      material.diffuseColor = (int(.5 * hit.x() + 10.) + int(.5 * hit.z())) & 1
                                  ? QVector3D(.3f, .0f, .5f)
                                  : QVector3D(.0f, .0f, .0f);
    }
  }
  return std::min(spheres_dist, checkerboard_dist) < 1000.f;
}

QVector3D cast_ray(const Ray &ray, const std::vector<Sphere> &spheres,
                   const std::vector<Plane> &planes,
                   const std::vector<Light> &lights, size_t depth = 0) {
  QVector3D point;
  QVector3D normal;
  Material material;

  if (depth > REFLECTION_DEPTH || !scene_intersect(ray, spheres, planes, point, normal, material)) {
    return BACKGROUND_COLOR;
  }

  QVector3D reflect_direction = reflect(ray.direction, normal).normalized();
  QVector3D refract_direction = refract(ray.direction, normal, material.refractiveIndex).normalized();
  QVector3D reflect_origin = QVector3D::dotProduct(reflect_direction, normal) < 0 // offset the original point to avoid occlusion by the object itself
          ? point - normal * 1e-3f
          : point + normal * 1e-3f;
  QVector3D refract_origin = QVector3D::dotProduct(refract_direction, normal) < 0
          ? point - normal * 1e-3f
          : point + normal * 1e-3f;
  QVector3D reflect_color = cast_ray(Ray(reflect_origin, reflect_direction), spheres, planes, lights, depth + 1);
  QVector3D refract_color = cast_ray(Ray(refract_origin, refract_direction), spheres, planes, lights, depth + 1);

  auto diffuse_light_intensity = 0.f;
  auto specular_light_intensity = 0.f;
  for (size_t i = 0; i < lights.size(); i++) {
    QVector3D light_direction = (lights[i].position - point).normalized();
    auto light_distance = (lights[i].position - point).length();

    QVector3D shadow_origin = QVector3D::dotProduct(light_direction, normal) < 0 // checking if the point lies in the shadow of the lights[i]
            ? point - normal * 1e-3f
            : point + normal * 1e-3f;
    QVector3D shadow_point;
    QVector3D shadow_normal;
    Material tmpmaterial;

    if (scene_intersect(Ray(shadow_origin, light_direction), spheres, planes, shadow_point, shadow_normal,
                        tmpmaterial) && (shadow_point - shadow_origin).length() < light_distance)
      continue;

    diffuse_light_intensity += lights[i].intensity * std::max(0.f, QVector3D::dotProduct(light_direction, normal));
    specular_light_intensity += powf(std::max(0.f, QVector3D::dotProduct(reflect(light_direction, normal), ray.direction)),
                                     material.specularFactor) * lights[i].intensity;
  }
  auto k = std::exp(-(point - ray.origin).length() / 100.f);
  auto obj_color = material.diffuseColor * diffuse_light_intensity * material.albedo.x() +
      LIGHT_COLOR * specular_light_intensity * material.albedo.y() + reflect_color * material.albedo.z() + refract_color * material.albedo.w();
  return mix(obj_color, BACKGROUND_COLOR, k);
}

int main(int argc, char *argv[]) {

  QString filter = "nearest";

  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("task5");
  QCoreApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Getting parametrs");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption WidthOption("W",
      QCoreApplication::translate("main", "Width."),
      QCoreApplication::translate("main", "Picture width value"));
  parser.addOption(WidthOption);

  QCommandLineOption HeightOption("H",
      QCoreApplication::translate("main", "Height."),
      QCoreApplication::translate("main", "Picture height value"));
  parser.addOption(HeightOption);

  QCommandLineOption FilterOption("F",
      QCoreApplication::translate("main", "Filter."),
      QCoreApplication::translate("main", "Filter value"));
  parser.addOption(FilterOption);

  parser.process(app);
  if (parser.isSet(WidthOption) && parser.isSet(HeightOption) && parser.isSet(FilterOption)) {
    WIDTH = parser.value(WidthOption).toInt();
    HEIGHT = parser.value(HeightOption).toInt();
    filter = parser.value(FilterOption);
    if (filter != "nearest" && filter != "linear") {
      throw std::invalid_argument("The filter can be either nearest or linear");
    }
  }

  Material ivory(1.0f, QVector4D(0.6f, 0.3f, 0.0f, 0.0f), QVector3D(0.4f, 0.4f, 0.3f),50.f);
  Material glass(1.5, QVector4D(0.0f, 0.5f, 0.1f, 0.8f), QVector3D(0.6f, 0.7f, 0.8f), 125.f);
  Material rubber(1.0f, QVector4D(0.9f, 0.1f, 0.0f, 0.0f), QVector3D(0.1f, 0.0f, 0.3f),10.f);
  Material mirror(1.0f, QVector4D(0.0f, 10.0f, 0.8f, 0.0f), QVector3D(1.0f, 1.0f, 1.0f),1425.f);
  Material metal(1.0f, QVector4D(0.3f, 0.3f, 0.09f, 0.0f), QVector3D(0.5f, 0.5f, 0.5f),100.f);
  Material plane_mater;

  std::vector<Sphere> spheres;
  spheres.emplace_back(Sphere(QVector3D(-4.f, -0.5f, -16.f), 2.f, ivory));
  spheres.emplace_back(Sphere(QVector3D(-1.0f, -1.5f, -12.f), 2.f, glass));
  spheres.emplace_back(Sphere(QVector3D(1.5f, -0.5f, -18.f), 3.f, rubber));
  spheres.emplace_back(Sphere(QVector3D(7.f, 5.f, -18.f), 4.f, mirror));
  spheres.emplace_back(Sphere(QVector3D(-9.f, 3.5f, -24.f), 2.5f, metal));


  std::vector<Plane> planes;
  planes.emplace_back(Plane(QVector3D(0.f, -4.f, 0.f), QVector3D(0.f, 1.f, 0.f), plane_mater));

  std::vector<Light> lights;
  lights.emplace_back(Light(QVector3D( 20.f, 30.f, -25.f), 1.5f));
  lights.emplace_back(Light(QVector3D( 20.f, 20.f,  20.f), 2.f));
  lights.emplace_back(Light(QVector3D(0.f, 20.f,  0.f), 2.5f));

  QImage result(WIDTH, HEIGHT, QImage::Format_RGB32);

  QVector3D resColor;
  for (auto y = 0; y < result.height(); y++) {
    for (auto x = 0; x < result.width(); x++) {
      auto dir_x = (x + 0.5f) - result.width() / 2.f;
      auto dir_y = -(y + 0.5f) + result.height() / 2.f;
      auto dir_z = -result.height() / (2.f * std::tan(FOV / 2.f));
      Ray ray(QVector3D(0.f, 0.f, 0.f), QVector3D(dir_x, dir_y, dir_z).normalized());
      resColor = cast_ray(ray, spheres, planes, lights);
      result.setPixel(x, y,qRgb(std::min(int(resColor.x() * 255), 255),
                           std::min(int(resColor.y() * 255), 255),
                           std::min(int(resColor.z() * 255), 255)));
    }
  }

  if (filter == "nearest")
    result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::FastTransformation).save("result.png");
  else
    result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation).save("result.png");

  return 0;
}