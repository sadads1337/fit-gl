#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void requestColor(int i);

  void requestSphere();

  void requestColorAm();
  void requestColorDir();
  void requestColorPnt();
  void requestColorPrj();

  void requestActivate();
  void requestRotation();
  void requestRotateFlag();
  void requestLightFactors();

  void requestDirPos();
  void requestPntPos();
private:
  QColorDialog color;
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
