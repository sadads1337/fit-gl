#include "MainWindow.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  app.setApplicationName("Task 4");

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  auto const window = std::make_shared<fgl::MainWindow>();
  window->showNormal();

  return app.exec();
}