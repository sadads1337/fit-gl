#include <QWidget>
#include <QHBoxLayout>
#include <QRadioButton>
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
  GLWidget* cube;


};
