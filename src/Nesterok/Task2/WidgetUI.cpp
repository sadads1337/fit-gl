#include "WidgetUI.h"


auto WidgetUI::createToolBar() {
  toolBar = new QHBoxLayout(this);

  auto nLabel = new QLabel("N:");
  toolBar->addWidget(nLabel);

  factorBox = new QSpinBox();
  factorBox->setValue(1);
  factorBox->setMinimum(1);
  factorBox->setValue(3);
  toolBar->addWidget(factorBox);

  auto morphLabel = new QLabel("Morph level:");
  toolBar->addWidget(morphLabel);

  slider = new QSlider(Qt::Horizontal);
  toolBar->addWidget(slider);
}

WidgetUI::WidgetUI(QWidget* parent):QWidget(parent){
  QVBoxLayout* vbox = new QVBoxLayout(this);

  createToolBar();
  vbox->addLayout(toolBar);

  cube = new GLWidget();
  vbox->addWidget(cube);

  connect(factorBox, qOverload<int>(&QSpinBox::valueChanged), cube,
          &GLWidget::changeN);
  connect(slider, qOverload<int>(&QSlider::valueChanged), cube,
          &GLWidget::changeFactor);
}
