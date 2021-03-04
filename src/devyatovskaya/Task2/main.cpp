#include "cubemorphing.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CubeMorphing w;
    w.show();
    return a.exec();
}
