#include "CommonWidget.h"
#include "MainWindow.h"
#include <type_traits>

namespace {

template <typename T, typename = std::enable_if_t<std::is_pointer<T>::value>>
using owner = T;

auto createSlider(float min_value, float max_value, float tick_value) {
  float min = min_value;
  float max = max_value;
  float tick = tick_value;
  auto *const slider = owner<QSlider *>(new QSlider(Qt::Horizontal));
  slider->setRange(min, max);
  slider->setSingleStep(tick);
  slider->setTickPosition(QSlider::TicksRight);
  return slider;
}
} // namespace

CommonWidget::CommonWidget() {

  auto *const Mwindow = owner<fgl::MainWindow *>(new fgl::MainWindow);
  auto *const tSlider = createSlider(0, 100, 10);
  auto *const color = owner<QColorDialog *>(new QColorDialog);
  color->setOptions(QColorDialog::DontUseNativeDialog |
                    QColorDialog::NoButtons);

  auto *const container = owner<QGridLayout *>(new QGridLayout);
  container->addWidget(Mwindow, 0, 1, 3, 2);
  container->addWidget(tSlider, 3, 1, 1, 2);
  container->addWidget(new QLabel("Morphed_param"), 3, 0, 1, 1);
  container->addWidget(color, 0, 0, 3, 1);

  auto *const mainLayout = owner<QVBoxLayout *>(new QVBoxLayout);

  auto *const w = owner<QWidget *>(new QWidget);
  w->setLayout(container);
  mainLayout->addWidget(w);
  setLayout(mainLayout);

  connect(tSlider, &QSlider::valueChanged, Mwindow,
          &fgl::MainWindow::set_morph_param);
  connect(color, &QColorDialog::currentColorChanged, Mwindow,
          &fgl::MainWindow::set_color);
}