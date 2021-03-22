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
		{	{"cube_morphing"},
                    {"Shaders\\v_cube_morphing.glsl", "Shaders\\f_cube_morphing.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },
		
		{	{"light"},
                {"Shaders\\Lighting\\v_light_source.glsl", "Shaders\\Lighting\\f_light_source.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },
		
		{	{"guro_lighting"},
                {"Shaders\\Lighting\\v_guro_lighting.glsl", "Shaders\\Lighting\\f_guro_lighting.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{	{"phong_lighting"},
                {"Shaders\\Lighting\\v_phong_lighting.glsl", "Shaders\\Lighting\\f_phong_lighting.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} }
	};
};
