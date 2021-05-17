#include <QApplication>
#include <QSurfaceFormat>

#include <QColorDialog>
#include <QMainWindow>


#include "CubeWindow.hpp"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);//сглаживание 
  format.setVersion(2, 1);

  fgl::CubeWindow window{};
  window.setFormat(format);
  window.resize(1366, 600);
  window.show();

  window.setAnimated(true);

  return app.exec();
}
