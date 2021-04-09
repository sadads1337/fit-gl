#include <QApplication>
#include <QSurfaceFormat>
#include "CommonWidget.h"

int main(int argc, char **argv) {
      QApplication app(argc, argv);

      app.setApplicationName("Task 3");

      QSurfaceFormat format;
      format.setSamples(16);
      format.setVersion(2, 1);
      format.setDepthBufferSize(24);
      QSurfaceFormat::setDefaultFormat(format);

      auto const window = std::make_shared<CommonWidget> ();
      window->showMaximized();

      return app.exec();
}