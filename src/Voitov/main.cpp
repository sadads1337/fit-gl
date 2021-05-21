#include <QApplication>
#include <QSurfaceFormat>
#include "uiwindow.h"
//change cube color - c
//change back color - b
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    geometry::Cube *cube = new geometry::Cube();
    cube->init(1.0f);

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
    delete cube;
    return 0;
}
