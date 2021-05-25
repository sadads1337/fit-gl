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

    virtual QVector<QVector3D> getVertexes() const noexcept = 0;
    virtual QVector<GLint> getIndexes() const noexcept = 0;

    virtual void setColor(const QVector3D rgb) = 0;

    [[nodiscard]] virtual QVector4D getColor() const noexcept = 0;

    [[nodiscard]] virtual QVector3D getRotationAxis() const noexcept = 0;

    virtual void setRotationAxis(const QVector3D rAxis) = 0;
};
}
