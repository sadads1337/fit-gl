#include <QApplication>
#include <QSurfaceFormat>
#include <QDesktopWidget>
#include "Widget.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Cube");

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}