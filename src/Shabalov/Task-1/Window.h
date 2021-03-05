#pragma once

#include "Widget.h"
#include <QColorDialog>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

class Window : public QWidget {
  Q_OBJECT

public:
  Window();

private:
  static std::unique_ptr<QSlider> createSlider();

  std::unique_ptr<Widget> widget;
  std::unique_ptr<QSlider> xSlider;
  std::unique_ptr<QSlider> ySlider;
  std::unique_ptr<QSlider> zSlider;
  std::unique_ptr<QLabel> xlabel;
  std::unique_ptr<QLabel> ylabel;
  std::unique_ptr<QLabel> zlabel;
  std::unique_ptr<QColorDialog> color;
  std::unique_ptr<QVBoxLayout> mainLayout;
  std::unique_ptr<QGridLayout> container;
  std::unique_ptr<QWidget> w;
};
