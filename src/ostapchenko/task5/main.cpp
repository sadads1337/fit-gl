#include "Ray.h"
#include <QVector3D>
#include "QtMath"
#include "QImage"
#include "Hittable.h"
#include "Sphere.h"
#include <memory>
#include "Plane.h"

#include "QCoreApplication"
#include <QCommandLineParser>


int WIDTH = 640;
int HEIGHT = 480;

constexpr float PI = 3.141592F;

constexpr float AMBIENT_STRENGTH = 0.3F;
constexpr QVector3D AMBIENT_COLOR{1.0F, 1.0F, 1.0F};

constexpr QVector3D BACKGROUND_COLOR{0.0f,0.0f,0.3f};
constexpr QVector3D LIGHT_COLOR{1.0F, 1.0F, 1.0F};
constexpr QVector3D LIGHT_POS{0.0F, 6.0F, 0.0F};
constexpr float LIGHT_INTENSITY = 1.5F;
constexpr QVector3D CAMERA_POS{0.0F, 1.1F, 5.0F};

inline QVector3D mix(const QVector3D &a, const QVector3D &b, const float k) {
  return a * k + b * (1 - k);
}

inline QVector3D reflect(const QVector3D &d, const QVector3D &n) {
  return d - 2.f * n * QVector3D::dotProduct(d, n) ;
}

QVector3D refract(const QVector3D &incident, const QVector3D &normal, const float n_1, const float n_2=1.f) {
  auto cos_1 = - std::max(-1.f, std::min(1.f, QVector3D::dotProduct(incident, normal)));
  if (cos_1 < 0.f) return refract(incident, -normal, n_2, n_1);
  auto ratio = n_2 / n_1;
  auto cos_2 = sqrtf(1 - ratio * ratio * (1 - cos_1 * cos_1));
  return  ratio * incident + (ratio * cos_1 - cos_2) * normal;
}


QVector3D trace(const Ray& r, const std::vector<std::shared_ptr<Hittable>> &objects, int reflection_depth) {

   if(reflection_depth == 0)
      return BACKGROUND_COLOR;



  QVector3D ambien_coeff = AMBIENT_COLOR*AMBIENT_STRENGTH;

  for(const auto &o : objects){
    float diffuse_light_intensity = 0.0F;
    float specular_light_intensity = 0.0F;
    const auto rec = o->hit(r);
    if(rec.has_value()){
      QVector3D light_dir = (LIGHT_POS - rec->p).normalized();
     float light_distance = (LIGHT_POS - rec->p).length();
     QVector3D reflect_dir = reflect(r.direction(), rec->p).normalized();
     QVector3D refract_dir = refract(r.direction(), rec->normal, rec->material.refractiveIndex).normalized();
     QVector3D reflect_orig = QVector3D::dotProduct(reflect_dir,rec->normal) < 0 ? rec->p - rec->normal*1e-3f : rec->p + rec->normal*1e-3f;
     QVector3D refract_orig = QVector3D::dotProduct(refract_dir, rec->normal) < 0 ? rec->p - rec->normal*1e-3f : rec->p + rec->normal*1e-3f;
     QVector3D reflect_color = trace(Ray(reflect_orig, reflect_dir), objects, reflection_depth-1);
     QVector3D refract_color = trace(Ray(refract_orig, refract_dir), objects, reflection_depth-1);


       QVector3D shadow_orig = QVector3D::dotProduct(light_dir,rec->normal) < 0 ? rec->p - rec->normal*1e-3f : rec->p + rec->normal*1e-3f;
       const auto  shadow_rec = o->hit(Ray(shadow_orig, light_dir));
       if(!(shadow_rec.has_value()) || shadow_rec->t > light_distance){
          diffuse_light_intensity = std::max(0.f, QVector3D::dotProduct(light_dir,rec->normal));
          specular_light_intensity = std::pow(std::max(0.f, QVector3D::dotProduct(reflect(light_dir, rec->normal),r.direction())), rec->material.specularFactor)*LIGHT_INTENSITY;
     }
      auto k = std::exp(-(rec->p-r.origin()).length()/100.f);
      auto resultColor = ambien_coeff*rec->color + rec->color * diffuse_light_intensity*rec->material.albedo.x()
                         +  LIGHT_COLOR*specular_light_intensity * rec->color*rec->material.albedo.y() + reflect_color *  rec->color*rec->material.albedo.z() + refract_color*  rec->color * rec->material.albedo.w();
          return mix(resultColor, BACKGROUND_COLOR, k );

      }
  }
  return BACKGROUND_COLOR;
}



int main(int argc, char *argv[]){

  QString filter = "nearest";

  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("Ray-tracing");
  QCoreApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Getting parametrs");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption WidthOption(QStringList() << "width" << "width-value",
                                           QCoreApplication::translate("main", "Picture width"),
                                           QCoreApplication::translate("main", "Picture width value"));
  parser.addOption(WidthOption);

  QCommandLineOption HeightOption(QStringList() << "height" << "height-value",
                                 QCoreApplication::translate("main", "Picture height"),
                                 QCoreApplication::translate("main", "Picture height value"));
  parser.addOption(HeightOption);

  QCommandLineOption FilterOption(QStringList() << "filter" << "filter-value",
                                  QCoreApplication::translate("main", "Filter"),
                                  QCoreApplication::translate("main", "Filter value"));
  parser.addOption(FilterOption);

  parser.process(app);
  //if there are arguments, they will be set, if not, then by default
  if(parser.isSet(WidthOption) && parser.isSet(HeightOption) && parser.isSet(FilterOption) ) {
    WIDTH = parser.value(WidthOption).toInt();
    HEIGHT = parser.value(HeightOption).toInt();
    filter = parser.value(FilterOption);
    if(filter != "nearest" && filter != "linear"){
      throw std::invalid_argument("The filter can be either nearest or linear");
    }
  }



  Material ivory{ 50., 1.0, QVector4D(0.6f, 0.3f, 0.1f, 0.0f)};
  Material rubber{10., 1.0, QVector4D(0.9f, 0.1f, 0.0f, 0.0f)};
  Material mirror{ 1425., 1.0, QVector4D(0.0f, 10.0f, 0.8f, 0.0f)};
  Material glass{ 125., 1.5, QVector4D(0.0f, 0.5f, 0.1f, 0.8f)};

  std::vector<std::shared_ptr<Hittable>> objects;
  objects.emplace_back(std::make_shared<Sphere>(QVector3D(-2.2f,0.5f,0.0f), 0.5, ivory, QVector3D(1.0f, 1.0f, 0.0f)));
  objects.emplace_back(std::make_shared<Sphere>(QVector3D(1.2f,0.5f,0.0f), 0.5, rubber,QVector3D  (0.1f, 0.1f, 0.3f)));
  objects.emplace_back(std::make_shared<Sphere>(QVector3D(0.0f,0.5f,0.0f), 0.5, mirror, QVector3D(1.0f, 1.0f, 1.0f)));
  objects.emplace_back(std::make_shared<Sphere>(QVector3D(-1.1f,0.5f,0.0f), 0.5, glass, QVector3D(0.6f, 0.7f, 0.8f)));

  objects.emplace_back(std::make_shared<Plane>(QVector3D(),QVector3D(0, 1, 0)));


  QImage result(WIDTH * 2, HEIGHT * 2, QImage::Format_ARGB32);
  for (int y = 0; y < result.height(); ++y) {
    for (int x = 0; x < result.width(); ++x) {

        auto dir_x = (x + 0.5f) - result.width() / 2.f;
        auto dir_y = -(y + 0.5f) + result.height() / 2.f;
        auto dir_z = -result.height() / (2.f * std::tan(PI / 6.f));
        Ray ray = Ray(CAMERA_POS, QVector3D(dir_x, dir_y, dir_z).normalized());
        QVector3D color = trace(ray, objects, 5);

        result.setPixelColor(x, y, qRgb(std::min(int(color.x()*255),255), std::min(int(color.y()*255),255),std::min(int(color.z()*255), 255)));

    }
  }


  if(filter == "nearest"){
  result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::FastTransformation)
      .save("result.png");
  }
  else{
    result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        .save("result.png");
  }

  return 0;
}