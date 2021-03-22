#pragma once
#include <QVector3D>
#include <QVector2D>



struct GLVertex
{
	QVector3D coordinate;
	QVector3D normal;
	QVector3D color;
	QVector2D texture;

	QVector3D tangent;
	QVector3D bitangent;
};