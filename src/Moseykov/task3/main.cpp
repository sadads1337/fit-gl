
#include "MyWidget.h"
#include "SquareWindow.hpp"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);

  auto window = new MyWidget();
  window->setMaximumSize(1280, 1024);
  window->showMaximized();

  return app.exec();
}
