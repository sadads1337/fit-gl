#pragma once

#include <QColorDialog>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_facesButton_clicked();

  void on_edgesButton_clicked();

  void change_face(int arg1);

  void on_morphFactorSlider_valueChanged(int value);

private:
  Ui::MainWindow *ui = nullptr;
  QColorDialog *colorDialog;
};
