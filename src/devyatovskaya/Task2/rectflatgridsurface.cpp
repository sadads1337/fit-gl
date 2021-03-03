#include "rectflatgridsurface.hpp"

rectFlatGridSurface::rectFlatGridSurface(size_t steps, const QColor& face_color, const QColor& edge_color)
    : arrayBuf_(QOpenGLBuffer::VertexBuffer),
      indexBuf_(QOpenGLBuffer::IndexBuffer),
      face_color_(face_color),
      edge_color_(edge_color)
{
    initializeOpenGLFunctions();
    arrayBuf_.create();
    indexBuf_.create();

    initialize(steps);
    load();
}

rectFlatGridSurface::rectFlatGridSurface(const rectFlatGridSurface& other, const QMatrix4x4& transformation)
    : vertices_(other.vertices_),
      indices_(other.indices_),
      indexBuf_(QOpenGLBuffer::IndexBuffer),
      face_color_(other.face_color_),
      edge_color_(other.edge_color_)
{
    initializeOpenGLFunctions();
    arrayBuf_.create();
    indexBuf_.create();
    transform(transformation);
    load();
}

rectFlatGridSurface::~rectFlatGridSurface()
{
    destroy();
}

void rectFlatGridSurface::draw(QOpenGLShaderProgram& program)
{
    arrayBuf_.bind();
    indexBuf_.bind();

    // Set vertex location attribute
    auto vertex_location = program.attributeLocation("posAttr");
    program.enableAttributeArray(vertex_location);
    program.setAttributeBuffer(vertex_location, GL_FLOAT, 0, 3);

    if (drawEdges_)
        drawEdges(program);

    if (drawFaces_)
        drawFaces(program);

    arrayBuf_.release();
    indexBuf_.release();
}

void rectFlatGridSurface::drawEdges(QOpenGLShaderProgram& program)
{
    // Set unifor color for edges
    program.setUniformValue("global_color", edge_color_);

    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.f);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
}

void rectFlatGridSurface::drawFaces(QOpenGLShaderProgram& program)
{
    // Set uniform color for cube's faces
    program.setUniformValue("global_color", face_color_);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.5, 1.);
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
}

void rectFlatGridSurface::initialize(size_t steps)
{
    vertices_.reserve((steps + 1) * (steps + 1));
    indices_.reserve( 6 * steps * steps);
    float step = 1.f / steps;

    for (size_t j = 0; j < steps + 1; ++j){
        for (size_t i = 0; i < steps + 1; ++i){
            vertices_.emplace_back(-0.5f + step * i, -0.5f + step * j, 0.5f);
        }
    }
    for (size_t j = 0; j < steps; ++j){
        for (size_t i = 0; i < steps; ++i){
            auto k = i + (j + 1) * (steps + 1);
            auto p = i + j * (steps + 1);
            indices_.push_back(k);
            indices_.push_back(p);
            indices_.push_back(p + 1);

            indices_.push_back(p + 1);
            indices_.push_back(k + 1);
            indices_.push_back(k);
        }
    }
}

void rectFlatGridSurface::setFaceColor(const QColor& color)
{
    face_color_ = color;
}

void rectFlatGridSurface::setEdgeColor(const QColor& color)
{
    edge_color_ = color;
}

QColor rectFlatGridSurface::getFaceColor() const
{
    return face_color_;
}

QColor rectFlatGridSurface::getEdgeColor() const
{
    return edge_color_;
}

void rectFlatGridSurface::transform(const QMatrix4x4& matrix)
{
    for (auto& vertex : vertices_){
        vertex = matrix * vertex;
    }
    reload();
}

rectFlatGridSurface rectFlatGridSurface::getTransformated(const QMatrix4x4& matrix)
{
    auto copy = *this;
    copy.transform(matrix);
    return copy;
}

void rectFlatGridSurface::destroy()
{
    arrayBuf_.destroy();
    indexBuf_.destroy();
}

void rectFlatGridSurface::load()
{
    arrayBuf_.bind();
    indexBuf_.bind();
    arrayBuf_.allocate(vertices_.data(),vertices_.size()
                       * sizeof(QVector3D));
    indexBuf_.allocate(indices_.data(), indices_.size()
                       * sizeof(GLushort));
}

void rectFlatGridSurface::reload()
{
    arrayBuf_.bind();
    arrayBuf_.allocate(vertices_.data(), vertices_.size()
                       * sizeof(QVector3D));
}
