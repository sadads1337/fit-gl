#pragma once

#include <QMainWindow>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_facesButton_clicked();

    void on_edgesButton_clicked();

    void on_faceNumSpinbox_valueChanged(int arg1);

    void on_morphFactorSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    QColorDialog* colorDialog;
};

