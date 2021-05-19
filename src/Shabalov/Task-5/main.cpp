#include <QImage>
#include <QColor>
#include <QOpenGLFunctions>
#include <QVector3D>
#include <cmath>
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Plane.h"
#include <memory>



constexpr auto WIDTH = 1280;
constexpr auto HEIGHT = 960;
constexpr auto PI = 3.14159265358979323846;
constexpr auto FOV = PI/3.;
constexpr auto MAX_REFLECTIONS = 4;
constexpr auto BACKGROUND_COLOR = QVector3D(0.2f, 0.7f, 0.8f);
constexpr auto offset = 1e-3;



[[nodisacrd]] auto mix(const QVector3D &a, const QVector3D &b, const float k){
    return k * a + (1 - k) * b;
}


[[nodisacrd]] auto reflect(const QVector3D &incident, const QVector3D &normal) {
return incident - 2.f * normal * (QVector3D::dotProduct(incident, normal));
}


[[nodisacrd]] auto refract(const QVector3D &incident, const QVector3D &normal, const float n_1, const float n_2=1.f) {
    const auto cosine_1 = - std::max(-1.f, std::min(1.f, QVector3D::dotProduct(incident, normal)));

    if (cosine_1 >= 0.f) {
        const auto ratio = n_2 / n_1;
        const auto cosine_2 = sqrtf(1 - ratio * ratio * (1 - cosine_1 * cosine_1));
        return ratio * incident + (ratio * cosine_1 - cosine_2) * normal;
    }
    return refract(incident, -normal, n_2, n_1);
}


[[nodisacrd]] auto scene_intersect(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Plane> &planes, QVector3D &hit, QVector3D &normal, Material &material) {
    auto spheres_dist = std::numeric_limits<float>::max();
    for (const auto & sphere : spheres) {
        auto dist_i = std::numeric_limits<float>::max();
        if (sphere.ray_intersect(ray, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = ray.origin + ray.direction * dist_i;
            normal = (hit - sphere.center).normalized();
            if(sphere.material.isTexture()) {
                int u = (sphere.material.image.width()-1) * (1 + atan2(normal.z(), normal.x()) / PI) * 0.5f;
                int v = (sphere.material.image.height()-1) * acosf(normal.y()) / PI;
                QColor tmp = sphere.material.image.pixel(u, v);
                material.diffuseColor = QVector3D(tmp.redF(), tmp.greenF(), tmp.blueF());
            }else {
                material = sphere.material;
            }
        }
    }
    auto planes_dist = std::numeric_limits<float>::max();
    for (const auto & plane : planes) {
        auto dist_i = std::numeric_limits<float>::max();
        if (plane.ray_intersect(ray, dist_i) && dist_i < spheres_dist) {
            planes_dist = dist_i;
            hit = ray.origin + ray.direction * dist_i;
            normal = plane.normal;
            material.diffuseColor = (int(.5*hit.x()+10.) + int(.5*hit.z())) & 1 ? QVector3D(.9f, .9f, .9f) : QVector3D(.0f, .0f, .0f);
        }
    }
    return std::min(spheres_dist, planes_dist)<1000.f;
}


[[nodisacrd]] auto cast_ray(const Ray &ray, const std::vector<Sphere> &spheres, const std::vector<Plane> &planes, const std::vector<Light> &lights, size_t depth=0){
    QVector3D point;
    QVector3D normal;
    Material material;

    if (depth > MAX_REFLECTIONS || !scene_intersect(ray, spheres, planes, point, normal, material)){
        return BACKGROUND_COLOR;
    }
    const auto reflect_direction = reflect(ray.direction, normal).normalized();
    const auto refract_direction = refract(ray.direction, normal, material.refractiveIndex).normalized();
    const auto reflect_origin = QVector3D::dotProduct(reflect_direction, normal) < 0 ? point - normal*offset : point + normal*offset;
    const auto refract_origin = QVector3D::dotProduct(refract_direction, normal) < 0 ? point - normal*offset : point + normal*offset;
    Ray reflect_ray = {.origin = reflect_origin, .direction = reflect_direction};
    Ray refract_ray = {.origin = refract_origin, .direction = refract_direction};
    const auto reflect_color = cast_ray(reflect_ray, spheres, planes, lights, depth + 1);
    const auto refract_color = cast_ray(refract_ray, spheres, planes, lights, depth + 1);

    auto diffuse_light_intensity = 0.f;
    auto specular_light_intensity = 0.f;
    for(auto light : lights) {
        const auto light_direction = (light.position - point).normalized();
        const auto light_distance = (light.position - point).length();
        const auto shadow_origin = QVector3D::dotProduct(light_direction, normal) < 0 ? point - normal*offset : point + normal*offset;
        QVector3D shadow_point;
        QVector3D shadow_normal;
        Material tmpmaterial;
        Ray light_ray = {.origin = shadow_origin, .direction = light_direction};
        if (scene_intersect(light_ray, spheres, planes, shadow_point, shadow_normal, tmpmaterial) && (shadow_point - shadow_origin).length() < light_distance)
            continue;
        diffuse_light_intensity  += light.intensity * std::max(0.f, QVector3D::dotProduct(light_direction, normal));
        specular_light_intensity += powf(std::max(0.f, QVector3D::dotProduct(reflect(light_direction, normal), ray.direction)), material.specularFactor) * light.intensity;
    }
    const auto k = std::exp(-(point-ray.origin).length()/100.f);
    const auto obj_color = material.diffuseColor * diffuse_light_intensity * material.proportion.x()
    + QVector3D(1., 1., 1.)*specular_light_intensity * material.proportion.y()
    + reflect_color*material.proportion.z()
    + refract_color*material.proportion.w();
    return mix(obj_color, BACKGROUND_COLOR, k);
}


int main(){
    Material ivory(QVector3D(0.4f, 0.4f, 0.3f), 50., 1.0, QVector4D(0.6f, 0.3f, 0.1f, 0.0f));
    Material rubber(QVector3D(0.1f, 0.1f, 0.3f), 10., 1.0, QVector4D(0.9f, 0.1f, 0.0f, 0.0f));
    Material mirror(QVector3D(1.0f, 1.0f, 1.0f), 1425., 1.0, QVector4D(0.0f, 1.0f, 0.8f, 0.0f));
    Material glass(QVector3D(0.6f, 0.7f, 0.8f), 125., 1.5, QVector4D(0.0f, 0.5f, 0.1f, 0.8f));
    QImage mars_tex = QImage(":/textures/mars.jpg");
    Material mars(std::move(mars_tex));
    QImage earth_tex = QImage(":/textures/earth.jpg");
    Material earth(std::move(earth_tex));
    Material plane_mater;

    std::vector<Sphere> spheres;
    spheres.emplace_back(Sphere(QVector3D(-2,    0,   -14), 2, ivory));
    spheres.emplace_back(Sphere(QVector3D(-0.5, -1.5, -10), 2, glass));
    spheres.emplace_back(Sphere(QVector3D( 3, -0.5, -18), 3, rubber));
    spheres.emplace_back(Sphere(QVector3D( 10,    7,   -20), 4, mirror));
    spheres.emplace_back(Sphere(QVector3D(8,    0,   -16), 2, earth));
    spheres.emplace_back(Sphere(QVector3D(-8,    0,   -16), 2, mars));

    std::vector<Plane> planes;
    planes.emplace_back(Plane(QVector3D(0,-4,0),QVector3D(0,1,0), plane_mater));

    std::vector<Light>  lights;
    Light light_1 = {.position = QVector3D( 30, 50, -25), .intensity = 1.5f};
    Light light_2 = {.position = QVector3D( 30, 20,  30), .intensity = 2.0f};
    Light light_3 = {.position = QVector3D(0, 20,  0), .intensity = 2.5f};

    lights.emplace_back(light_1);
    lights.emplace_back(light_2);
    lights.emplace_back(light_3);


    QImage result(WIDTH, HEIGHT, QImage::Format_RGB32);
    QVector3D resColor;
    for(auto y = 0; y < result.height(); y++){
        for(auto x = 0; x < result.width(); x++){
            const auto dir_x =  (x + 0.5f) -  result.width()/2.f;
            const auto dir_y = -(y + 0.5f) + result.height()/2.f;
            const auto dir_z = -result.height()/(2.f*std::tan(FOV/2.f));
            Ray ray = {.origin = QVector3D(0,0,0), .direction = QVector3D(dir_x,dir_y,dir_z).normalized()};
            resColor = cast_ray(ray, spheres, planes,  lights);
            result.setPixel(x,y, qRgb(std::min(int(resColor.x()*255),255), std::min(int(resColor.y()*255),255),std::min(int(resColor.z()*255), 255)));
        }
    }
    result.save("result.png");
    return 0;
}
