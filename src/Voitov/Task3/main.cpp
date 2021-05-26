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

    for(unsigned int i = cubePosition.size() - 1; i >= 1; --i)
    {
        delete cube[i];
    }

    return 0;
}

//#include <QApplication>
//#include <QSurfaceFormat>
//#include "uiwindow.h"
//#include <iostream>
////c - change cube color
////b - change back color
//#include <array>

//std::array<QVector3D, 9u> cubePosition{
//     QVector3D(0.3f/*left-right*/, 0.0f/*up-down*/, -2.5f), QVector3D(1.4f, 0.0f, -2.5f),
//    QVector3D(-0.8f, -0.7f, -1.6f), QVector3D(0.5f, 0.5f, -1.5f),
//    QVector3D(-0.35f, 0.05f, -0.8f),  QVector3D(1.3f, -0.8f, -2.5f),
//    QVector3D(-0.2f, 1.0f, -2.5f),   QVector3D(0.3f, -1.5f, -4.5f)
//};

//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);

//    QSurfaceFormat format;
//    format.setSamples(16);
//    format.setVersion(2, 1);

//    UIWindow window;
//    window.setFormat(format);
//    window.resize(640, 480);

//    geometry::Cube*cube;

//    for(unsigned int i = 0; i < cubePosition.size(); i++)
//    {
//        cube = new geometry::Cube;
//        cube->init(0.5f, cubePosition[i]);
//        window.addObj(cube);
//    }


////    QVector<geometry::Cube*>* cube = new QVector<geometry::Cube*>;
////    for(unsigned int i = 0; i < cubePosition.size(); i++)
////    {
////        cube->append(new geometry::Cube());
////        (*cube)[i]->init(0.5f, cubePosition[i]);
////    }

//    //window.addObj(cube);
//    window.show();
//    window.setAnimated(true);

//    app.exec();

////    for(int i = cubePosition.size() - 1; i >= 0; --i)
////    {
////        delete (*cube)[i];
////    }
////    delete cube;

//    {
//    //std::unique_ptr<geometry::figure> scene;
//    //geometry::Cube* cube = new geometry::Cube [cubePosition.size()];
//    //for(int i )



//    //window.addObj(scene);

////    geometry::Cube *cubeObject0 = new geometry::Cube();
////    cubeObject0->init(0.5f, cubePosition[0]);
////    std::unique_ptr<geometry::figure> cube0(cubeObject0);
////    window.addObj(cube0);


////    geometry::Cube *cubeObject1 = new geometry::Cube();
////    cubeObject1->init(0.5f, cubePosition[1]);
////    std::unique_ptr<geometry::figure> cube1(cubeObject1);
////    window.addObj(cube1);
//}
///*
//    QVector<geometry::Cube*> cubeObjects;
//    for(unsigned int i = 0; i < cubePosition.size(); i++)
//    {
//        cubeObjects.append(new geometry::Cube());
//        cubeObjects[i]->init(0.5f, cubePosition[i]);
//    }
////    std::unique_ptr<QVector<geometry::figure*>> cubes(cubeObjects);


//    window.show();
//    window.setAnimated(true);

//    for(unsigned int i = 0; i < cubePosition.size(); i++)
//    {
//        delete cubeObjects[i];
//    }
//*/

//    return 0;
//}
