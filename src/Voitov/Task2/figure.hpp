#pragma once
#include <QVector3D>
#include <QVector4D>
#include <QVector>
#include <QOpenGLBuffer>

namespace geometry{

class figure
{
public:
    virtual ~figure() = default;

    QVector<QVector3D> getVertexes();
    QVector<GLint> getIndexes();

    void setColor(QVector3D rgb);
    QVector4D getColor();

    QVector3D getRotationAxis();

    void setRotationAxis(QVector3D rAxis);
protected:
    QVector<QVector3D> gVertexes;
    QVector<GLint> gIndexes;

    QOpenGLBuffer vBuf;
    QOpenGLBuffer indBuf{QOpenGLBuffer::IndexBuffer};

    QVector4D Color{0.0, 1.0, 0.0, 1};
    QVector3D rotationAxis{0., 1., 0.};
};
}
