
#include "cubewidget.hpp"
#include "mainwindow.hpp"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
  QApplication::setStyle("Fusion");
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  app.setApplicationName("cube");
  app.setApplicationVersion("0.1");

  MainWindow main_window;
  main_window.show();

  return app.exec();
}
