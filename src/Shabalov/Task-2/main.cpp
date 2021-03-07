#include "MainWindow.h"
#include "Widget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

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