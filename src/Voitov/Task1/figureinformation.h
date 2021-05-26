#ifndef FIGUREINFORMATION_H
#define FIGUREINFORMATION_H
#include"figure.hpp"


namespace geometry{
class FigureInformation : public figure
{
public:
    QVector<QVector3D> getVertexes() const noexcept override;
    QVector<GLint> getIndexes() const noexcept override;

    void setColor(const QVector3D rgb) override;

    [[nodiscard]] QVector4D getColor() const noexcept override;
    [[nodiscard]] QVector3D getRotationAxis() const noexcept override;

    void setRotationAxis(const QVector3D rAxis) override;

protected:
    QVector<QVector3D> gVertexes;
    QVector<GLint> gIndexes;

    QOpenGLBuffer vBuf;
    QOpenGLBuffer indBuf{QOpenGLBuffer::IndexBuffer};

    QVector4D Color{0.0, 1.0, 0.0, 1};
    QVector3D rotationAxis{0., 1., 0.};
};
}
#endif // FIGUREINFORMATION_H
