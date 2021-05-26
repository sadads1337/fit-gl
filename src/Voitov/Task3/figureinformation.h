#ifndef FIGUREINFORMATION_H
#define FIGUREINFORMATION_H
#include"figure.hpp"


namespace geometry{
class FigureInformation : public figure
{
public:
    QVector<VertexData> getVertexes() const noexcept override;
    QVector<GLushort> getIndexes() const noexcept override;

    [[nodiscard]] QVector3D getRotationAxis() const noexcept override;

    [[nodiscard]] QVector3D getCenter() const noexcept override;

protected:
    QVector<VertexData> gVertexes;
    QVector<GLushort> gIndexes;

    QOpenGLBuffer vBuf;
    QOpenGLBuffer indBuf{QOpenGLBuffer::IndexBuffer};

    QVector3D center_ = {0.0, 0.0, 0.0};
    QVector3D rotationAxis{0., 1., 0.};
};
}
#endif // FIGUREINFORMATION_H
