#pragma once
#include "GLMeshRenderer.h"

class GLSimpleMeshRenderer : public GLMeshRenderer
{

public:
	GLSimpleMeshRenderer(GLMesh& mesh, GLTransform& transform, GLMaterial& material);
	
	void render(QOpenGLFunctions_3_0& functions, const GLCamera& camera, const std::map<light_sptr, obj_sptr>& lights) override;

private:
	void upload_lights_details(const std::map<light_sptr, obj_sptr>& lights) const;
	void upload_texture_details(QOpenGLFunctions_3_0& functions);
};
