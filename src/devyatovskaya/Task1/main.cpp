#include "cubewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    CubeWindow window;
    window.setFormat(format);
    window.resize(640, 480);

    window.show();

    window.setAnimated(true);

    return app.exec();
}
