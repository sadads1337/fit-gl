#include <QVector3D>
#include <cmath>
#include "Types.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include <QImage>
#include <QColor>
#include <QOpenGLFunctions>
#include "QCoreApplication"
#include <QCommandLineParser>
#include <iostream>

int WIDTH = 640;
int HEIGHT = 480;
constexpr float PI = 3.141592F;
constexpr auto MAX_REFLECTIONS = 4;
constexpr QVector3D BACKGROUND_COLOR{0.7f, 0.7f, 0.9f};
constexpr QVector3D LIGHT_COLOR{1.0F, 1.0F, 1.0F};
constexpr QVector3D LIGHT_POS{0.0F, 4.0F, 0.0F};
constexpr float LIGHT_INTENSITY = 1.5F;
constexpr QVector3D CAMERA_POS{0.0F, 1.0F, 3.0F};

QVector3D mix(const QVector3D &a, const QVector3D &b, const float k){
    return a * k + b*(1 - k);
}


QVector3D reflect(const QVector3D &incident, const QVector3D &normal) {
return incident - 2.f * normal * (QVector3D::dotProduct(incident, normal));
}


QVector3D refract(const QVector3D &incident, const QVector3D &normal, const float n_1, const float n_2=1.f) {
    auto cos_1 = - std::max(-1.f, std::min(1.f, QVector3D::dotProduct(incident, normal)));
    if (cos_1 < 0.f) return refract(incident, -normal, n_2, n_1);
    auto ratio = n_2 / n_1;
    auto cos_2 = sqrtf(1 - ratio * ratio * (1 - cos_1 * cos_1));
    return  ratio * incident + (ratio * cos_1 - cos_2) * normal;
}


bool intersect(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Plane> &planes, QVector3D &hit, QVector3D &normal, Material &material, const QImage &texture) {
    auto spheres_dist = std::numeric_limits<float>::max();
    // QImage TEXTURE = QImage(":/textures/texture.jpg");
    for (const auto & sphere : spheres) {
        auto dist_i = std::numeric_limits<float>::max();
        if (sphere.intersect(ray, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = ray.origin + ray.direction * dist_i;
            normal = (hit - sphere.center).normalized();
            material = sphere.material;
           
        }
    }
    float planes_dist = std::numeric_limits<float>::max();
    for (const auto & plane : planes) {
        auto dist_i = std::numeric_limits<float>::max();
        if (plane.intersect(ray, dist_i) && dist_i < spheres_dist) {
            planes_dist = dist_i;
            hit = ray.origin + ray.direction * dist_i;
            normal = plane.normal;
            int width = texture.width()-1;
            int height = texture.height()-1;
            if (std::abs(hit.x()) > 0 && std::abs(hit.x()) < width)
                width = std::abs(hit.x());
            if (std::abs(hit.y()) > 0 && std::abs(hit.y()) < height)
                height = std::abs(hit.y());
            QColor color = texture.pixel(width, height);
            material.diffuseColor = QVector3D(color.redF(), color.greenF(), color.blueF());
            
        }
    }
    return std::min(spheres_dist, planes_dist)<1000.f;
}


QVector3D cast_ray(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Plane> &planes, const QImage texture, size_t depth=0){
    QVector3D point;
    QVector3D normal;
    Material material;

    if (depth > MAX_REFLECTIONS || !intersect(ray, spheres, planes, point, normal, material, texture)){
        return BACKGROUND_COLOR;
    }
    QVector3D reflect_direction = reflect(ray.direction, normal).normalized();
    QVector3D refract_direction = refract(ray.direction, normal, material.refractiveIndex).normalized();
    QVector3D reflect_origin = QVector3D::dotProduct(reflect_direction, normal) < 0 ? point - normal*1e-3f : point + normal*1e-3f;
    QVector3D refract_origin = QVector3D::dotProduct(refract_direction, normal) < 0 ? point - normal*1e-3f : point + normal*1e-3f;
    QVector3D reflect_color = cast_ray(Ray(reflect_origin, reflect_direction), spheres, planes, texture, depth + 1);
    QVector3D refract_color = cast_ray(Ray(refract_origin, refract_direction), spheres, planes, texture,  depth + 1);

    auto diffuse_light_intensity = 0.f;
    auto specular_light_intensity = 0.f;
    QVector3D light_direction = (LIGHT_POS - point).normalized();
    auto light_distance = (LIGHT_POS - point).length();
    QVector3D shadow_origin = QVector3D::dotProduct(light_direction, normal) < 0 ? point - normal*1e-3f : point + normal*1e-3f;
    QVector3D shadow_point;
    QVector3D shadow_normal;
    Material matter;
 
    if (!intersect(Ray(shadow_origin, light_direction), spheres, planes, shadow_point, shadow_normal, matter, texture) && (shadow_point - shadow_origin).length() < light_distance){
        diffuse_light_intensity  = LIGHT_INTENSITY * std::max(0.f, QVector3D::dotProduct(light_direction, normal));
        specular_light_intensity = powf(std::max(0.f, QVector3D::dotProduct(reflect(light_direction, normal), ray.direction)), material.specularFactor) * LIGHT_INTENSITY;
    }
    auto k = std::exp(-(point-ray.origin).length()/100.f);
    auto result_color = material.diffuseColor * diffuse_light_intensity * material.albedo.x() + specular_light_intensity * LIGHT_COLOR * material.albedo.y()
    + reflect_color * material.albedo.z() + refract_color*material.albedo.w();
    return mix(result_color, BACKGROUND_COLOR, k);
}

int main(int argc, char *argv[]){
    QImage texture = QImage(":/textures/texture1.jpg");
    QString filter = "nearest";
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("task5");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Settings");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption WidthOption(QStringList() << "width" << "width", QCoreApplication::translate("main", "Width"));
    parser.addOption(WidthOption);

    QCommandLineOption HeightOption(QStringList() << "height" << "height", QCoreApplication::translate("main", "Height"));
    parser.addOption(HeightOption);

    QCommandLineOption FilterOption(QStringList() << "filter" << "filter", QCoreApplication::translate("main", "Filter"));
    parser.addOption(FilterOption);

    parser.process(app);
    if(parser.isSet(FilterOption) && parser.isSet(WidthOption) && parser.isSet(HeightOption) ) {
        WIDTH = parser.value(WidthOption).toInt();
        HEIGHT = parser.value(HeightOption).toInt();
        filter = parser.value(FilterOption);
        if(filter != "nearest" && filter != "linear"){
        throw std::invalid_argument("Incorrect value");
        }
    }
    
    Material empty;
    Material ivory(QVector3D(0.1f, 0.5f, 0.6f), 50., 1.0, QVector4D(0.6f, 0.3f, 0.1f, 0.0f));
    Material rubber(QVector3D(0.3f, 0.1f, 0.3f), 10., 1.0, QVector4D(0.9f, 0.1f, 0.0f, 0.0f));
    Material mirror(QVector3D(1.0f, 1.0f, 1.0f), 1425., 1.0, QVector4D(0.0f, 1.0f, 0.8f, 0.0f));
    Material glass(QVector3D(0.7f, 0.8f, 0.8f), 125., 1.5, QVector4D(0.0f, 0.5f, 0.1f, 0.8f));

    std::vector<Sphere> spheres;
    spheres.emplace_back(Sphere(QVector3D(-7, -1.5, -15), 2, ivory));
    spheres.emplace_back(Sphere(QVector3D(-2, -1.5, -15), 2, glass));
    spheres.emplace_back(Sphere(QVector3D(3, -1.5, -15), 2, rubber));
    spheres.emplace_back(Sphere(QVector3D(8, -1.5, -15), 2, mirror));

    std::vector<Plane> planes;
    planes.emplace_back(Plane(QVector3D(0, -4, 0), QVector3D(0, 1, 0), empty));

    QImage result(WIDTH, HEIGHT, QImage::Format_RGB32);
    QVector3D res;
    for(auto y = 0; y < result.height(); y++){
        for(auto x = 0; x < result.width(); x++){
            auto dir_x =  (x + 0.5f) -  result.width()/2.f;
            auto dir_y = -(y + 0.5f) + result.height()/2.f;
            auto dir_z = -result.height() / (2.f * std::tan(PI / 6.f));
            Ray ray(CAMERA_POS, QVector3D(dir_x, dir_y, dir_z).normalized());
            res = cast_ray(ray, spheres, planes, texture);
            result.setPixelColor(x, y, qRgb(std::min(int(res.x()*255),255), std::min(int(res.y()*255),255),std::min(int(res.z()*255), 255)));
        }
    }
   if(filter == "nearest"){
    result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    result.save("result.png");
  }
  if(filter == "linear"){
    result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    result.save("result.png");
  }

  return 0;
}