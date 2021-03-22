#pragma once

#include <QOpenGLFunctions_3_0>
class GLScene;



enum render_mode : uint64_t
{
	gl_line = 0x00000001U,
	gl_fill = 0x00000002U,
	gl_cull_face_back = 0x0000004U,
	gl_cull_face_front = 0x00000008U
};

class GLSceneRenderer final : protected QOpenGLFunctions_3_0
{
public:
	GLSceneRenderer();
	
	void init();
	void render(GLScene& scene);


	void set_mode(uint8_t mode);
	void reset_mode(uint8_t mode);
private:
	uint8_t mode_;
	void render_lights_objects(GLScene& scene) const;
};
