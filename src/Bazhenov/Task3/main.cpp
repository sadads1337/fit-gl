#include <QApplication>
#include <QSurfaceFormat>

#include "MainWindow.hpp"

constexpr int GL_VERSION_MAJOR = 2;
constexpr int GL_VERSION_MINOR = 1;

constexpr int Q_SURFACE_NUM_SAMPLES = 16;
constexpr int Q_SURFACE_DEPTH_BUFFER_SIZE = 24;

constexpr QSize WINDOW_SIZE(640, 480);

int main(int argc, char **argv) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(Q_SURFACE_NUM_SAMPLES);
  format.setVersion(GL_VERSION_MAJOR, GL_VERSION_MINOR);
  format.setDepthBufferSize(Q_SURFACE_DEPTH_BUFFER_SIZE);

  Bazhenov::MainWindow mainWindow;
  mainWindow.setFormat(format);
  mainWindow.resize(WINDOW_SIZE);
  mainWindow.show();

  mainWindow.setAnimated(true);

  return QGuiApplication::exec();
}