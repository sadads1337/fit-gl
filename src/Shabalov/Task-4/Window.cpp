#include "Window.h"
#include "Widget.h"
#include <type_traits>

namespace {

template <typename T, typename = std::enable_if_t<std::is_pointer<T>::value>>
using owner = T;

[[nodiscard]] auto createSlider() {
  constexpr auto min = 0;
  constexpr auto max = 100;
  constexpr auto tick = 10;
  auto *const slider = owner<QSlider *>(new QSlider(Qt::Horizontal));
  slider->setRange(min, max);
  slider->setSingleStep(tick);
  slider->setTickPosition(QSlider::TicksRight);
  return slider;
}
} // namespace

Window::Window() {
  auto *const widget = owner<Widget *>(new Widget);

  auto *const xSlider = createSlider();
  auto *const ySlider = createSlider();
  auto *const zSlider = createSlider();
  auto *const container = owner<QGridLayout *>(new QGridLayout);

  container->addWidget(widget, 0, 0, 2, 3);

  container->addWidget(xSlider, 2, 2, 1, 1);
  container->addWidget(ySlider, 3, 2, 1, 1);
  container->addWidget(zSlider, 4, 2, 1, 1);
  container->addWidget(new QLabel("X"), 2, 3, 1, 1);
  container->addWidget(new QLabel("Y"), 3, 3, 1, 1);
  container->addWidget(new QLabel("Z"), 4, 3, 1, 1);
  auto *const mainLayout = owner<QVBoxLayout *>(new QVBoxLayout);

  auto *const w = owner<QWidget *>(new QWidget);
  w->setLayout(container);
  mainLayout->addWidget(w);
  setLayout(mainLayout);

  connect(xSlider, &QSlider::valueChanged, widget, &Widget::setXRotation);
  connect(ySlider, &QSlider::valueChanged, widget, &Widget::setYRotation);
  connect(zSlider, &QSlider::valueChanged, widget, &Widget::setZRotation);

  xSlider->setValue(50);
  ySlider->setValue(50);
  zSlider->setValue(50);
}
