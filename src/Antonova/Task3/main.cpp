#include <QApplication>
#include <QSurfaceFormat>

#include "CubeWindow.hpp"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);

  fgl::CubeWindow window;
  window.setFormat(format);
  window.resize(640 * 2, 480 * 2);
  window.show();

  window.setAnimated(true);

  return app.exec();
}
