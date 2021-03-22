#pragma once
#include <map>
#include <string>
#include "GLScene.h"


class PreparedScenes
{
public:
	std::map<std::string, GLScene> scenes;

	void init();

private:
	GLScene default_scene();
};
