
#include <QApplication>
#include <QSurfaceFormat>

#include "TriangleWindow.hpp"

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);

  fgl::TriangleWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.show();

  window.setAnimated(true);

  return app.exec();
}
