#pragma once

#include <memory>

#include <QVector3D>

#include <Scene/SceneWindow.hpp>

#include <FirstShader.hpp>

namespace Kononov {

class ThirdWindow final : public SceneWindow {
public:
  void init() override;

private:
  void add_objects(QVector3D translation,
                   const std::shared_ptr<QOpenGLShaderProgram> &program);
};

} // namespace Kononov
