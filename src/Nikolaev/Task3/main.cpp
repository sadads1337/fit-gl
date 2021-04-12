#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setSamples(16);
  QSurfaceFormat::setDefaultFormat(format);

  app.setApplicationName("Morphing cube");
  app.setApplicationVersion("0.1");

  MainWindow widget;
  widget.show();

  return app.exec();
}
