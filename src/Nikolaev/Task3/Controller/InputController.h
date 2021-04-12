#ifndef FIT_GL_INPUTCONTROLLER_H
#define FIT_GL_INPUTCONTROLLER_H

#include <memory>
#include <unordered_set>

#include <QKeyEvent>
#include <QVector3D>

class InputController {
public:
  void keyPressEvent(QKeyEvent *event);

  void keyReleaseEvent(QKeyEvent *event);

  void update();

  unsigned int vertexFactor = 1U;

  enum Shaders {
    Phong = 0,
    Guaraud = 1
  };
  unsigned int currentShader = Phong;

private:
  std::unordered_set<int> pressedKeys;
};

#endif // FIT_GL_INPUTCONTROLLER_H
