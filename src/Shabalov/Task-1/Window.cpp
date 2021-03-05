#include "Window.h"
#include "Widget.h"

namespace {

template <typename T, typename = std::enable_if_t<std::is_pointer<T>::value>>
using owner = T;

[[nodiscard]] auto createSlider() {
  constexpr auto min = 0;
  constexpr auto max = 100;
  constexpr auto tick = 10;
  auto * const slider = owner<QSlider *>( new QSlider(Qt::Vertical));
  slider->setRange(min, max);
  slider->setSingleStep(tick);
  slider->setTickPosition(QSlider::TicksRight);
  return slider;
}

} // namespace

Window::Window() {
  auto * const widget = owner<Widget *>(new Widget);
  
  auto * const xSlider = createSlider();
  auto * const ySlider = createSlider();
  auto * const zSlider = createSlider();

  auto * const color = owner<QColorDialog *>(new QColorDialog);

  auto * const container = owner<QGridLayout *>(new QGridLayout);

  container->addWidget(widget, 0, 0, 2, 1);

  container->addWidget(xSlider, 1, 1, 1, 1);
  container->addWidget(ySlider, 1, 2, 1, 1);
  container->addWidget(zSlider, 1, 3, 1, 1);

  container->addWidget(color, 2, 0, 1, 3);

  container->addWidget(new QLabel("X"), 0, 1, 1, 1);
  container->addWidget(new QLabel("Y"), 0, 2, 1, 1);
  container->addWidget(new QLabel("Z"), 0, 3, 1, 1);

  auto * const mainLayout = owner<QVBoxLayout *>(new QVBoxLayout);

  auto * const w = owner<QWidget *>(new QWidget);
  w->setLayout(container);
  mainLayout->addWidget(w);
  setLayout(mainLayout);

  connect(xSlider, &QSlider::valueChanged, widget,
          &Widget::setXRotation);
  connect(ySlider, &QSlider::valueChanged, widget,
          &Widget::setYRotation);
  connect(zSlider, &QSlider::valueChanged, widget,
          &Widget::setZRotation);
  connect(color, &QColorDialog::currentColorChanged,
          widget, &Widget::setColor);

  constexpr auto defaultValue = 50;

  xSlider->setValue(defaultValue);
  ySlider->setValue(defaultValue);
  zSlider->setValue(defaultValue);

  color->setCurrentColor(QColor(Qt::gray));
}
