
#include <QApplication>
#include <QSurfaceFormat>

#include "CubeWindow.hpp"

int main(int argc, char **argv) {
  QApplication app(argc, argv); //application - holds events

  QSurfaceFormat format;
  format.setSamples(16); //Set the preferred number of samples per pixel when multisampling is enabled to numSamples. 
  //By default, multisampling is disabled -??????
  format.setVersion(2, 1); //Sets the desired major and minor OpenGL versions

  fgl::CubeWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.show();

  window.setAnimated(true);

  return app.exec();
}
