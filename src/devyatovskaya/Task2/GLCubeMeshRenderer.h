#pragma once
#include "GLMeshRenderer.h"

class GLCubeMeshRenderer : public GLMeshRenderer
{
public:
	
    void render();

private:

	void draw_edges();
	void draw_faces();
};
