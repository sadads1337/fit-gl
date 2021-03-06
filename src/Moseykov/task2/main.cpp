
#include <QApplication>
#include <QSurfaceFormat>
#include "MyWidget.h"
#include "SquareWindow.hpp"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);

  auto window = new MyWidget();
  window->setMaximumSize(500,500);
  window->showMaximized();

  return app.exec();
}
