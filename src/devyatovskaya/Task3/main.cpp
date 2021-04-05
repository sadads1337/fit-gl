#include "PhongLighting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	
    QSurfaceFormat format;
    format.setSamples(16);
    format.setVersion(2, 1);
    QSurfaceFormat::setDefaultFormat(format);

	
    PhongLighting w;
    w.resize(1280, 720);
    w.show();
    return a.exec();
}
