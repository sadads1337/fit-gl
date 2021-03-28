#pragma once
#include "GLMeshRenderer.h"

class GLSimpleMeshRenderer : public GLMeshRenderer
{

public:
    GLSimpleMeshRenderer(GLMesh& mesh, GLTransform& transform);
	
    void render(QOpenGLFunctions_3_0& functions, const GLCamera& camera) override;
};
