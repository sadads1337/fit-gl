#pragma once
#include <vector>
#include "GLScene.h"


class PreparedScenes
{
public:
	
	std::vector<GLScene> scenes;
	void init();

private:
    GLScene default_morphing(ShaderData& data);
	
    GLScene default_scene_sphere(ShaderData&);
    GLScene default_scene_cube(ShaderData&);
};
