
#include <QApplication>
#include <QSurfaceFormat>
#include "WidgetUI.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);
  format.setVersion(2, 1);
  QSurfaceFormat::setDefaultFormat(format);

  WidgetUI window;
  window.resize(640, 480);
  window.show();

//  window.setAnimated(true);

  return app.exec();
}
