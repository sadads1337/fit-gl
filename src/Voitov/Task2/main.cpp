#include <QApplication>
#include <QSurfaceFormat>
#include "uiwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    geometry::Cube *cubeObject = new geometry::Cube();
    cubeObject->init(3.0f, 10U);
    std::unique_ptr<geometry::figure> cube(cubeObject);

    QSurfaceFormat format;
    format.setSamples(16);
    format.setVersion(2, 1);

    UIWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.addObj(cube);
    window.show();

    window.setAnimated(true);

    app.exec();
    return 0;
}
