#pragma once
#include "GLMeshRendererGenerator.h"
#include "GLSimpleMeshRenderer.h"

class GLSimpleMeshRendererGenerator : public GLMeshRendererGenerator
{
public:
    std::shared_ptr<GLMeshRenderer> get_renderer(GLMesh&, GLTransform&) override;
};
