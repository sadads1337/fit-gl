#include <QApplication>
#include <QSurfaceFormat>

#include "MainWindow.hpp"

static const int GL_VERSION_MAJOR = 3;
static const int GL_VERSION_MINOR = 3;

static const int Q_SURFACE_NUM_SAMPLES = 16;
static const int Q_SURFACE_DEPTH_BUFFER_SIZE = 24;

static constexpr QSize WINDOW_SIZE(640, 480);

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(Q_SURFACE_NUM_SAMPLES);
  format.setVersion(GL_VERSION_MAJOR, GL_VERSION_MINOR);
  format.setDepthBufferSize(Q_SURFACE_DEPTH_BUFFER_SIZE);
  format.setOption(QSurfaceFormat::DebugContext);

  Kononov::MainWindow main_window;
  main_window.setFormat(format);
  main_window.resize(WINDOW_SIZE);
  main_window.show();

  main_window.setAnimated(true);

  return QGuiApplication::exec();
}
