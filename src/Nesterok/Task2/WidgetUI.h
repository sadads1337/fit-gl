#include "GLWidget.hpp"
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

#pragma once
class WidgetUI : public QWidget {
  Q_OBJECT

public:
  WidgetUI(QWidget *parent = 0);

private:
  auto createToolBar();

  QSpinBox *factorBox;
  QSlider *slider;
  GLWidget *cube;
  QHBoxLayout *toolBar;
};
