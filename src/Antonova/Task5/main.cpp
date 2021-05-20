#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include "Tracer.h"

#include "QImage"
#include "QtMath"
#include <memory>

#include "QCoreApplication"
#include <QCommandLineParser>

int WIDTH = 640;
int HEIGHT = 480;
QVector3D CAMERA_POS{0.0f, 2.0f, 6.0f};
float PI = 3.141592f;

int main(int argc, char *argv[]) {

  // PARSER & APP
  QString filter = "nearest";

  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("Ray-tracing");
  QCoreApplication::setApplicationVersion("1.0");

  QCommandLineParser parser;
  parser.setApplicationDescription("Getting parameters");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption WidthOption(
      QStringList() << "width"
                    << "width-value",
      QCoreApplication::translate("main", "Picture width"),
      QCoreApplication::translate("main", "Picture width value"));
  parser.addOption(WidthOption);

  QCommandLineOption HeightOption(
      QStringList() << "height"
                    << "height-value",
      QCoreApplication::translate("main", "Picture height"),
      QCoreApplication::translate("main", "Picture height value"));
  parser.addOption(HeightOption);

  QCommandLineOption FilterOption(
      QStringList() << "filter"
                    << "filter-value",
      QCoreApplication::translate("main", "Filter"),
      QCoreApplication::translate("main", "Filter value"));
  parser.addOption(FilterOption);

  parser.process(app);
  // if there are arguments, they will be set, if not, then by default
  if (parser.isSet(WidthOption) && parser.isSet(HeightOption) &&
      parser.isSet(FilterOption)) {
    WIDTH = parser.value(WidthOption).toInt();
    HEIGHT = parser.value(HeightOption).toInt();
    filter = parser.value(FilterOption);
    if (filter != "nearest" && filter != "linear") {
      throw std::invalid_argument("The filter can be either nearest or linear");
    }
  }

  // LIGHT
  LightConditions light_conditions;
  light_conditions.background_color =
      QVector3D(0.0f / 255, 0.0f / 255, 0.0f / 255);
  light_conditions.ambient_color = QVector3D(1.0f, 1.0f, 1.0f);
  light_conditions.ambient_strength = 0.5f;
  light_conditions.light_color = QVector3D(1.0f, 1.0f, 1.0f);
  light_conditions.light_pos = QVector3D(0.0f, 6.0f, 0.0f);
  light_conditions.light_intensity = 1.5f;

  // OBJECTS
  Material shiny{50., 1.0, QVector4D(0.6f, 1.0f, 0.1f, 0.0f)};
  Material matt{10., 1.0, QVector4D(0.9f, 0.1f, 0.0f, 0.0f)};
  Material mirror{1425., 1.0, QVector4D(0.0f, 10.0f, 0.8f, 0.0f)};
  Material glass{125., 1.5, QVector4D(0.0f, 0.5f, 0.1f, 0.8f)};

  std::vector<std::shared_ptr<Hittable>> objects;
  objects.emplace_back(std::make_shared<Sphere>(
      QVector3D(-2.0f, 3.0f, -0.5f), 1.0, shiny,
      QVector3D(150.0f / 255, 153.0f / 255, 250.0f / 255)));

  objects.emplace_back(std::make_shared<Sphere>(
      QVector3D(0.7f, 1.0f, 0.6f), 0.5, matt, QVector3D(0.1f, 0.1f, 0.3f)));

  objects.emplace_back(std::make_shared<Sphere>(
      QVector3D(-1.0f, 0.5f, 0.3f), 0.7, mirror, QVector3D(1.0f, 1.0f, 1.0f)));

  objects.emplace_back(std::make_shared<Sphere>(
      QVector3D(2.1f, 1.5f, -0.5f), 0.8, glass, QVector3D(0.8f, 0.8f, 1.0f)));

  objects.emplace_back(
      std::make_shared<Plane>(QVector3D(), QVector3D(0, 1, 0)));

  // MAKE IMAGE
  Tracer tracer;

  QImage result(WIDTH * 2, HEIGHT * 2, QImage::Format_ARGB32);
  for (int y = 0; y < result.height(); ++y) {
    for (int x = 0; x < result.width(); ++x) {

      auto dir_x = (x + 0.5f) - result.width() / 2.f;
      auto dir_y = -(y + 0.5f) + result.height() / 2.f;
      auto dir_z = -result.height() / (2.f * std::tan(PI / 6.f));
      Ray ray = Ray(CAMERA_POS, QVector3D(dir_x, dir_y, dir_z).normalized());
      QVector3D color = tracer.trace(ray, objects, 5, light_conditions);

      result.setPixelColor(x, y,
                           qRgb(std::min(int(color.x() * 255), 255),
                                std::min(int(color.y() * 255), 255),
                                std::min(int(color.z() * 255), 255)));
    }
  }

  if (filter == "nearest") {
    result.scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::FastTransformation)
        .save("result.png");
  } else {
    result
        .scaled(WIDTH, HEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        .save("result.png");
  }

  return 0;
}
