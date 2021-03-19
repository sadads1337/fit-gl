#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainwindow w;
    w.setFixedSize(1390,615);
    w.setWindowTitle("FPS_Test");
    w.show();
    return a.exec();
}
