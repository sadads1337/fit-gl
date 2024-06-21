#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "dialog.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), dialog(new Dialog(this)) {
  ui->setupUi(this);

  QObject::connect(dialog, &Dialog::ObjectMaterialChanged, ui->Scene,
                   &SceneWidget::setObjectMaterial);
  QObject::connect(ui->Scene, &SceneWidget::MaterialShininess, dialog,
                   &Dialog::setShininessVal);
  QObject::connect(ui->Scene, &SceneWidget::newMaterial, dialog,
                   &Dialog::addMaterial);
  QObject::connect(dialog, &Dialog::AmbientChanged, ui->Scene,
                   &SceneWidget::setMaterialAmbient);
  QObject::connect(dialog, &Dialog::DiffuseChanged, ui->Scene,
                   &SceneWidget::setMaterialDiffuse);
  QObject::connect(dialog, &Dialog::SpecularChanged, ui->Scene,
                   &SceneWidget::setMaterialSpecular);
  QObject::connect(dialog, &Dialog::ShininessChanged, ui->Scene,
                   &SceneWidget::setMaterialShininess);
  QObject::connect(dialog, &Dialog::DirLightIntensityChanged, ui->Scene,
                   &SceneWidget::setDirInt);
  QObject::connect(dialog, &Dialog::DirLightColorChanged, ui->Scene,
                   &SceneWidget::setDirColor);
  QObject::connect(dialog, &Dialog::PointLightColorChanged, ui->Scene,
                   &SceneWidget::setPointColor);
  QObject::connect(dialog, &Dialog::SpotLightColorChanged, ui->Scene,
                   &SceneWidget::setSpotColor);
  QObject::connect(dialog, &Dialog::DirLightDirectionChanged, ui->Scene,
                   &SceneWidget::setDirDirection);
  QObject::connect(dialog, &Dialog::PointLightIntensityChanged, ui->Scene,
                   &SceneWidget::setPointInt);
  QObject::connect(dialog, &Dialog::PointLightConstChanged, ui->Scene,
                   &SceneWidget::setPointConst);
  QObject::connect(dialog, &Dialog::PointLightLinChanged, ui->Scene,
                   &SceneWidget::setPointLin);
  QObject::connect(dialog, &Dialog::PointLightQuadChanged, ui->Scene,
                   &SceneWidget::setPointQuad);
  QObject::connect(dialog, &Dialog::SpotLightIntensityChanged, ui->Scene,
                   &SceneWidget::setSpotInt);
  QObject::connect(dialog, &Dialog::SpotLightConstChanged, ui->Scene,
                   &SceneWidget::setSpotConst);
  QObject::connect(dialog, &Dialog::SpotLightLinChanged, ui->Scene,
                   &SceneWidget::setSpotLin);
  QObject::connect(dialog, &Dialog::SpotLightQuadChanged, ui->Scene,
                   &SceneWidget::setSpotQuad);
  QObject::connect(dialog, &Dialog::CutOffChanged, ui->Scene,
                   &SceneWidget::setCutOff);
  QObject::connect(dialog, &Dialog::OuterCutOffChanged, ui->Scene,
                   &SceneWidget::setOuterCutOff);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_SceneOptionsButton_clicked() { dialog->show(); }

void MainWindow::on_doubleSpinBox_valueChanged(double arg1) {
  ui->Scene->setGridStepLen(arg1);
}
