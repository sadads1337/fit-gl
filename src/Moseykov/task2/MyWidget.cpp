#include "MyWidget.h"

namespace {

template<typename T, typename = std::enable_if_t<std::is_pointer<T>::value>>
using main = T;

auto morph_slider(int min_value,int max_value, int tick_value) {
  auto *const slider = main<QSlider *>(new QSlider(Qt::Horizontal));
  slider->setRange(min_value, max_value);
  slider->setSingleStep(tick_value);
  slider->setTickPosition(QSlider::TicksRight);
  return slider;
}
}

MyWidget::MyWidget()
{
  auto * const my_window = main<fgl::SquareWindow *>(new fgl::SquareWindow);
  auto * const tSlider = morph_slider(0, 1000, 50);
  auto * const container = main<QGridLayout *>(new QGridLayout);
  auto * const mainLayout = main<QVBoxLayout *>(new QVBoxLayout);
  auto * const w = main<QWidget *>(new QWidget);
  container->addWidget(my_window);
  container->addWidget(tSlider);
  w->setLayout(container);
  mainLayout->addWidget(w);
  setLayout(mainLayout);
  connect(tSlider, &QSlider::valueChanged, my_window, &fgl::SquareWindow::change_morph_param);
}