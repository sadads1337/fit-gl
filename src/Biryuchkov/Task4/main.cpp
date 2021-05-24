
#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindow w;
  w.setFixedSize(1070,580);
  w.setWindowTitle("FPS_Test");
  w.show();
  return a.exec();
}
