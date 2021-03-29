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

		{	{"light_source"},
                {":/Shaders/Lighting/v_light_source.glsl",
               ":/Shaders/Lighting/f_light_source.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{	{"phong_wo_normal_mapping"},
                {":/Shaders/Lighting/v_phong_lighting_wo_normal_mapping.glsl",
               ":/Shaders/Lighting/f_phong_lighting_wo_normal_mapping.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{	{"phong_normal_mapping"},
                {":/Shaders/Lighting/v_phong_lighting_normal_mapping.glsl",
               ":/Shaders/Lighting/f_phong_lighting_normal_mapping.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },
		
		{	{"guro_wo_normal_mapping"},
                {":/Shaders/Lighting/v_guro_lighting_wo_normal_mapping.glsl",
               ":/Shaders/Lighting/f_guro_lighting_wo_normal_mapping.glsl", std::make_shared<GLSimpleMeshRendererGenerator>()} },

		{ {"morphing"},
                {":/Shaders/v_morphing.glsl",":/Shaders/f_morphing.glsl",
                 std::make_shared<GLSimpleMeshRendererGenerator>()} }
	};
};
