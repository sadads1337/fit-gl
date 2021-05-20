#include "WidgetUI.h"


auto WidgetUI::createToolBar() {
  toolBar = new QHBoxLayout(this);

  GouraundButton = new QRadioButton("Gouraund");
  toolBar->addWidget(GouraundButton);
  GouraundButton->toggle();

  PhongButton = new QRadioButton("Phong");
  toolBar->addWidget(PhongButton);

  ambientBox = new QCheckBox("ambient");
  toolBar->addWidget(ambientBox);
  ambientBox->toggle();

  diffuseBox = new QCheckBox("diffuse");
  toolBar->addWidget(diffuseBox);
  diffuseBox->toggle();

  specularBox = new QCheckBox("specular");
  toolBar->addWidget(specularBox);
  specularBox->toggle();

}

WidgetUI::WidgetUI(QWidget* parent):QWidget(parent){
  QVBoxLayout* vbox = new QVBoxLayout(this);

  createToolBar();
  vbox->addLayout(toolBar);

  cube = new GLWidget();
  vbox->addWidget(cube);

  connect(PhongButton, &QRadioButton::toggled, cube,
          &GLWidget::changeType);
  connect(ambientBox, &QCheckBox::toggled, cube,
          &GLWidget::changeAmbient);
  connect(diffuseBox, &QRadioButton::toggled, cube,
          &GLWidget::changeDiffuse);
  connect(specularBox, &QRadioButton::toggled, cube,
          &GLWidget::changeSpecular);

}
