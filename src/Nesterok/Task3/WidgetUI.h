#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include "GLWidget.hpp"

#pragma once
class WidgetUI : public QWidget {
  Q_OBJECT

public:
  WidgetUI(QWidget *parent = 0);

private:
  auto createToolBar();
  QHBoxLayout *toolBar;
  QRadioButton* GouraundButton;
  QRadioButton* PhongButton;

  QCheckBox* ambientBox;
  QCheckBox* diffuseBox;
  QCheckBox* specularBox;

  GLWidget* cube;


};
