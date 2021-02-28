
#include <QApplication>
#include <QSurfaceFormat>

#include "SquareWindow.hpp"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);

  fgl::SquareWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.setTitle("Moseykov-First_task-Square");
  window.show();

  window.setAnimated(true);

  return app.exec();
}
