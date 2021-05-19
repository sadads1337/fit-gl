#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpinBox>
#include "GLWidget.hpp"

#pragma once
class WidgetUI : public QWidget {
  Q_OBJECT

public:
  WidgetUI(QWidget *parent = 0);

private:
  auto createToolBar();

  QSpinBox *factorBox;
  QSlider  *slider;
  GLWidget *cube;
  QHBoxLayout *toolBar;

};
