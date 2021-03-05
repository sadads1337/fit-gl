#include "cube.hpp"
#include <cmath>

Cube::Cube(size_t steps,
     QVector3D const& size,
     QColor const& face_color,
     QColor const& edge_color
)
{
    initialize(steps, face_color, edge_color, size);
}

void Cube::draw(QOpenGLShaderProgram& program)
{
    for (auto& face : faces_){
        face.draw(program);
    }
}

void Cube::scale(const QVector3D& scale)
{
    QMatrix4x4 scale_mat;
    scale_mat.scale(scale);

    for (auto& face : faces_){
        face.transform(scale_mat);
    }
}

void Cube::initialize(size_t steps,
                      QColor const& face_color,
                      QColor const& edge_color,
                      QVector3D const& size
                      )
{
    faces_.reserve(6);
    faces_.emplace_back(steps, face_color, edge_color);

    // Create rotation matrix for creating new surfaces
    QMatrix4x4 rotation;
    rotation.rotate(90.f, 0.f, 1.f);
    faces_.emplace_back(faces_.front(), rotation);

    rotation.rotate(90.f, 0.f, 1.f);
    faces_.emplace_back(faces_.front(), rotation);

    rotation.rotate(90.f, 0.f, 1.f);
    faces_.emplace_back(faces_.front(), rotation);

    rotation.rotate(90.f, 0.f, 1.f);

    rotation.rotate(90.f, 1.f, 0.f);
    faces_.emplace_back(faces_.front(), rotation);

    rotation.rotate(180.f, 1.f, 0.f);
    faces_.emplace_back(faces_.front(), rotation);

    scale(size);
}

void Cube::setEdgeColor(const QColor& color, int face)
{
    if (face == -1){
        for (auto& face : faces_){
            face.setEdgeColor(color);
        }
    }
    else {
        Q_ASSERT(face >= 0 && face < 6);
        faces_[face].setEdgeColor(color);
    }
}

QColor Cube::getFaceColor(int face)
{
    Q_ASSERT(face >= 0 && face < 6);
    return faces_[face].getFaceColor();
}

QColor Cube::getEdgeColor(int face)
{
    Q_ASSERT(face >= 0 && face < 6);
    return faces_[face].getEdgeColor();
}

void Cube::setFaceColor(const QColor& color, int face)
{
    if (face == -1){
        for (auto& face : faces_){
            face.setFaceColor(color);
        }
    }
    else {
        Q_ASSERT(face >= 0 && face < 6);
        faces_[face].setFaceColor(color);
    }
}

