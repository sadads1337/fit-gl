#include "scene.hpp"

Scene::Scene(QOpenGLFunctions &fucntions) : functions_(fucntions) {}

void Scene::initialize(Scene::ShaderProgramSptr object,
                       Scene::ShaderProgramSptr lightSrc) {
  objectShader_ = std::move(object);
  lightSourceShader_ = std::move(lightSrc);

  objectShader_->bind();
  objectShader_->setUniformValue("dirLightsCount", GLint(0));
  objectShader_->setUniformValue("pointLightsCount", GLint(0));
}

void Scene::addPointLightSource(Scene::PointLightSourseSPtr light) {
  light->initialize(lightSourceShader_);
  objects.push_back(std::static_pointer_cast<MeshObject>(light));
  pointLightSources.push_back(std::move(light));

  objectShader_->bind();
  objectShader_->setUniformValue("pointLightsCount",
                                 GLint(pointLightSources.size()));
}

void Scene::addDirectlyLightSource(Scene::DirectlyLightSourseSPtr light) {
  dirLightSources.push_back(std::move(light));

  objectShader_->bind();
  objectShader_->setUniformValue("dirLightsCount",
                                 GLint(dirLightSources.size()));
}

void Scene::addSpotLightSource(Scene::SpotLightSourseSPtr light) {
  spotLightsSources.push_back(std::move(light));

  objectShader_->bind();
  objectShader_->setUniformValue("spotLightsCount",
                                 GLint(spotLightsSources.size()));
}

void Scene::addRenderObject(Scene::RenderObjectSPtr object) {
  object->initialize(objectShader_);
  objects.push_back(std::move(object));
}

void Scene::renderAll() {
  objectShader_->bind();
  objectShader_->setUniformValue("dirLightsCount",
                                 GLint(dirLightSources.size()));
  objectShader_->setUniformValue("pointLightsCount",
                                 GLint(pointLightSources.size()));
  objectShader_->setUniformValue("spotLightsCount",
                                 GLint(spotLightsSources.size()));

  for (size_t i = 0; i < pointLightSources.size(); ++i) {
    pointLightSources[i]->uploadToShader(objectShader_, i);
  }
  for (size_t i = 0; i < dirLightSources.size(); ++i) {
    dirLightSources[i]->uploadToShader(objectShader_, i);
  }
  for (size_t i = 0; i < spotLightsSources.size(); ++i) {
    spotLightsSources[i]->uploadToShader(objectShader_, i);
  }
  for (auto &obj : objects) {
    obj->render(functions_);
  }
}

void Scene::clean() {
  objects.clear();
  dirLightSources.clear();
  pointLightSources.clear();
  spotLightsSources.clear();
}
