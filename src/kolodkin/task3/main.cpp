#include "mainwindow.hpp"
#include "scenewidget.hpp"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[]) {
  QApplication::setStyle("Fusion");
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow main_window;
  main_window.show();

  return app.exec();
}
