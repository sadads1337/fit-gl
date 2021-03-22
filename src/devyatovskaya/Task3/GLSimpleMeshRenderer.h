#pragma once
#include "GLMeshRenderer.h"

class GLSimpleMeshRenderer : public GLMeshRenderer
{

public:
	GLSimpleMeshRenderer(GLMesh& mesh, GLTransform& transform, GLMaterial& material)
		: GLMeshRenderer{ mesh, transform, material }
	{
	}
	
	void render(const GLCamera& camera, const std::map<light_sptr, obj_sptr>& lights) override;

private:
	void upload_lights_details(const std::map<light_sptr, obj_sptr>& lights) const;
};
