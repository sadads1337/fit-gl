#pragma once
#include <QVector3D>
#include <QVector4D>
#include <QVector>
#include <QOpenGLBuffer>

namespace geometry{

struct VertexData {
    VertexData(QVector3D position, QVector3D normal);
    QVector3D position;
    QVector3D norm;
};

class figure
{
public:
    virtual ~figure() = default;

    QVector<VertexData> getVertexes();
    QVector<GLushort> getIndexes();

    QVector3D getRotationAxis();
    QVector3D getCenter();
protected:
    QVector<GLushort> gIndexes;
    QVector<VertexData> gVertexes;

    QOpenGLBuffer vBuf;
    QOpenGLBuffer indBuf{QOpenGLBuffer::IndexBuffer};

    QVector3D center = {0.0, 0.0, 0.0};
    QVector3D rotationAxis{0., 1., 0.};
};
}
