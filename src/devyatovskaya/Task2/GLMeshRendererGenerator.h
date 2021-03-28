#pragma once
#include <memory>
class GLMeshRenderer;
class GLMesh;
class GLTransform;

class GLMeshRendererGenerator
{
public:

    virtual std::shared_ptr<GLMeshRenderer> get_renderer(GLMesh&, GLTransform&) = 0;
	virtual ~GLMeshRendererGenerator() = default;
};
