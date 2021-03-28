#pragma once
#include <QColor>
#include "GLMesh.h"


class GLMeshGenerator
{
public:
	GLMeshGenerator() = default;

	virtual GLMesh generate(const QColor& color) const = 0;
	virtual ~GLMeshGenerator() = default;
protected:	
	virtual void init_vertices(std::vector<GLVertex>& vertices, const QColor& color) const = 0;
	virtual void init_indices(std::vector<unsigned>& indices) const = 0;
};
