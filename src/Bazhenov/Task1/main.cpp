#include <QGuiApplication>
#include <QSurfaceFormat>

#include "MainWindow.hpp"

constexpr int GL_VERSION_MAJOR = 3;
constexpr int GL_VERSION_MINOR = 3;

constexpr int Q_SURFACE_NUM_SAMPLES = 16;
constexpr int Q_SURFACE_DEPTH_BUFFER_SIZE = 24;

constexpr QSize WINDOW_SIZE(640, 480);

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(Q_SURFACE_NUM_SAMPLES);
  format.setVersion(GL_VERSION_MAJOR, GL_VERSION_MINOR);
  format.setDepthBufferSize(Q_SURFACE_DEPTH_BUFFER_SIZE);
  format.setOption(QSurfaceFormat::DebugContext);

  Bazhenov::MainWindow mainWindow;
  mainWindow.setFormat(format);
  mainWindow.resize(WINDOW_SIZE);
  mainWindow.show();

  mainWindow.setAnimated(true);

  return QGuiApplication::exec();
}