#pragma once
#include <map>
#include "ShaderData.h"
#include "GLMeshRendererGenerator.h"
#include "GLSimpleMeshRendererGenerator.h"

class ShaderCollection final
{
public:
	
	inline static std::map<std::string, ShaderData> shaders =
	{
		{ {"morphing"},
                {"Shaders/v_morphing.glsl",
               "Shaders/f_morphing.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} }
	};
};
