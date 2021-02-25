
#include <QApplication>
#include <QSurfaceFormat>
#include <QColorDialog>
#include "SquareWindow.hpp"
#include <QMainWindow>
int main(int argc, char **argv) {
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);

  fgl::SquareWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.show();

  window.setAnimated(true);
  return a.exec();
}
