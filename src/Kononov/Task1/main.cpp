#include <QApplication>
#include <QSurfaceFormat>

#include "MainWindow.hpp"

int main(int argc, char **argv) {
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    format.setVersion(3, 3);
    format.setDepthBufferSize(24);
    format.setOption(QSurfaceFormat::DebugContext);

    Kononov::MainWindow main_window;
    main_window.setFormat(format);
    main_window.resize(640, 480);
    main_window.show();

    main_window.setAnimated(true);

    return app.exec();
}