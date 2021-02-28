
#include "SquareWindow.hpp"
#include <QApplication>
#include <QColorDialog>
#include <QMainWindow>
#include <QSurfaceFormat>
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
