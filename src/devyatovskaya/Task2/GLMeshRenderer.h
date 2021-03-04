#pragma once
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_0>
#include "GLMesh.h"
#include <QOffscreenSurface>


class GLMeshRenderer : protected QOpenGLFunctions_3_0
{
public:
	GLMeshRenderer();

    void init_renderer(GLMesh* mesh, const std::string& vertex, const std::string& fragment);
    virtual void render() = 0;


    QOpenGLShaderProgram& shader_program()
    {
        return shader_program_;
    }

	virtual ~GLMeshRenderer() = default;

	void reload()
	{
		init_vbo();
		init_ibo();
	}

protected:
	GLMesh* mesh_ = nullptr;

	QOpenGLBuffer vertex_buf_;
	QOpenGLBuffer index_buf_;
    QOpenGLShaderProgram shader_program_;


	void enable_attributes();
	void disable_attributes();

	
private:
	
    void init_shaders(const std::string& vertex, const std::string& fragment);
	void init_vbo();
	void init_ibo();
};
