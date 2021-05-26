#include <QApplication>
#include <QSurfaceFormat>
#include "uiwindow.h"
#include <iostream>
#include <array>
//c - change cube color
//b - change back color

std::array<QVector3D, 9u> cubePosition{
     QVector3D(0.3f/*left-right*/, 0.0f/*up-down*/, -2.5f), QVector3D(1.4f, 0.0f, -2.5f),
    QVector3D(-0.8f, -0.7f, -1.6f), QVector3D(0.5f, 0.5f, -1.5f),
    QVector3D(-0.35f, 0.05f, -0.8f),  QVector3D(1.3f, -0.8f, -2.5f),
    QVector3D(-0.2f, 1.0f, -2.5f),   QVector3D(0.3f, -1.5f, -4.5f)};


int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    format.setVersion(2, 1);

    UIWindow window;
    window.setFormat(format);
    window.resize(640, 480);

    QVector<geometry::Cube*> cube;
    for(unsigned int i = 0; i < cubePosition.size(); i++)
    {
        cube.append(new geometry::Cube());
        cube[i]->init(0.5f, cubePosition[i]);
        window.addObj(cube[i]);
    }
    window.show();
    window.setAnimated(true);

    app.exec();

    for(unsigned int i = 0; i < cubePosition.size(); i++)
    {
        delete cube[i];
    }

    return 0;
}
