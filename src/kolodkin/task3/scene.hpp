#pragma once

#include "direcltylight.hpp"
#include "lightsource.hpp"
#include "meshobject.hpp"
#include "pointlightsource.hpp"
#include "spotlightsource.hpp"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <memory>
#include <vector>

class Scene {
  using LightSourseSPtr = std::shared_ptr<LightSource>;
  using PointLightSourseSPtr = std::shared_ptr<PointLightSource>;
  using DirectlyLightSourseSPtr = std::shared_ptr<DirecltyLight>;
  using SpotLightSourseSPtr = std::shared_ptr<SpotLightSource>;
  using RenderObjectSPtr = std::shared_ptr<RenderObject>;
  using ShaderProgramSptr = std::shared_ptr<QOpenGLShaderProgram>;

  QOpenGLFunctions &functions_;
  ShaderProgramSptr objectShader_;
  ShaderProgramSptr lightSourceShader_;

public:
  std::vector<PointLightSourseSPtr> pointLightSources;
  std::vector<DirectlyLightSourseSPtr> dirLightSources;
  std::vector<SpotLightSourseSPtr> spotLightsSources;
  std::vector<RenderObjectSPtr> objects;

  Scene(QOpenGLFunctions &fucntions);

  void initialize(ShaderProgramSptr object, ShaderProgramSptr lightSrc);
  void addPointLightSource(PointLightSourseSPtr light);
  void addDirectlyLightSource(DirectlyLightSourseSPtr light);
  void addSpotLightSource(SpotLightSourseSPtr light);

  void addRenderObject(RenderObjectSPtr object);
  void renderAll();
  void clean();
};
