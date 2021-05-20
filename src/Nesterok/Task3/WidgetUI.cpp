#include "WidgetUI.h"


auto WidgetUI::createToolBar() {
  toolBar = new QHBoxLayout(this);

}

WidgetUI::WidgetUI(QWidget* parent):QWidget(parent){
  QVBoxLayout* vbox = new QVBoxLayout(this);

  createToolBar();
  vbox->addLayout(toolBar);

  cube = new GLWidget();
  vbox->addWidget(cube);

}
