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
    virtual QVector<VertexData> getVertexes() const noexcept = 0;
    virtual QVector<GLushort> getIndexes() const noexcept = 0;

    [[nodiscard]] virtual QVector3D getRotationAxis() const noexcept = 0;
    [[nodiscard]] virtual QVector3D getCenter() const noexcept = 0;

    virtual ~figure() = default;
};
}
