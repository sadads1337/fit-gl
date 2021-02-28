#include "cubewindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(32);

  fgl::CubeWindow window;
  window.setFormat(format);
  window.resize(800, 600);
  window.show();

  window.setAnimated(true);

  return app.exec();
}
