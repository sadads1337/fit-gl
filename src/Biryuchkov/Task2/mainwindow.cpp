#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      colorDialog(new QColorDialog(this)) {
  ui->setupUi(this);
  colorDialog->setOption(QColorDialog::NoButtons);

  QObject::connect(colorDialog, &QColorDialog::currentColorChanged,
                   ui->cubeWidget, &CubeWidget::setColor);
}

MainWindow::~MainWindow() {
  delete ui;
  delete colorDialog;
}

void MainWindow::on_facesButton_clicked() {
  ui->cubeWidget->setFaceMode();
  colorDialog->show();
}

void MainWindow::on_edgesButton_clicked() {
  ui->cubeWidget->setEdgeMode();
  colorDialog->show();
}

void MainWindow::change_face(const int arg1) {
  ui->cubeWidget->setCurrentFace(arg1);
}

void MainWindow::on_morphFactorSlider_valueChanged(const int value) {
  const auto factor =
      static_cast<float>(value) /
      (ui->morphFactorSlider->maximum() - ui->morphFactorSlider->minimum());
  ui->cubeWidget->setMorphFactor(factor);
  ui->morphFactorNumLabel->setText(QString::number(factor, 'f', 2));
}
