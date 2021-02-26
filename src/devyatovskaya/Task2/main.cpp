#include "cubewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

        CubeWidget widget;
        widget.setFixedSize(1200, 600);
        widget.show();

        return app.exec();
}
