#include "cubegeometry.h"

#include <QPushButton>

void CubeGeometry::InitGeometry()
{
    setVertices();
    setColor();
}

void CubeGeometry::DrawGeometry(QOpenGLShaderProgram* program)
{
    if(need_init_) {
        initializeOpenGLFunctions();
        need_init_ = false;
    }


    const auto vertex_location = program->attributeLocation("posAttr");
    Q_ASSERT(vertex_location != -1);
    const auto color_location = program->attributeLocation("colAttr");
    Q_ASSERT(color_location != -1);

    glVertexAttribPointer(vertex_location, 3, GL_FLOAT, GL_FALSE, 0, vertex_buf_.data());
    glVertexAttribPointer(color_location, 3, GL_FLOAT, GL_FALSE, 0, color_buf_.data());

    glEnableVertexAttribArray(vertex_location);
    glEnableVertexAttribArray(color_location);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);
    glDrawArrays(GL_TRIANGLE_STRIP, 10, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 14, 4);

    glDisableVertexAttribArray(vertex_location);
    glDisableVertexAttribArray(color_location);
}

void CubeGeometry::setVertices()
{
    const auto a = edge_len_ / 2;
    const auto dim = 3u;
    const auto sideSurfCount = 10u, topCount = 4u, bottomCount = 4u;

    Q_ASSERT(sideSurfCount + topCount + bottomCount == vertex_count_);

    for (auto i = 0u; i < sideSurfCount * dim; i += dim) {               /* side surface vertices */
        const auto idx = static_cast<int>(i / dim);
        vertex_buf_[i] = idx > 1 && idx < 6 ? a : -a;                         // x
        vertex_buf_[i + 1u] = idx % 2 == 0 ? a : -a;                          // y
        vertex_buf_[i + 2u] = idx > 3 && idx < 8 ? -a : a;                    // z
    }

    const auto topIdxEnd = topCount + sideSurfCount;
    for (auto i = sideSurfCount * dim; i < topIdxEnd * dim; i += dim) { /* top vertices */
        const auto idx = static_cast<int>(i / dim) - sideSurfCount;
        vertex_buf_[i] = idx % 2 == 0 ? -a : a;                               // x
        vertex_buf_[i + 1u] = a;                                              // y
        vertex_buf_[i + 2u] = idx > 1 ? -a : a;                               // z
    }

    const auto bottomIdxEnd = topIdxEnd + bottomCount;
    for (auto i = topIdxEnd * dim; i < bottomIdxEnd * dim; i += dim) { /* bottom vertices */
        const auto idx = static_cast<int>(i / dim) - topIdxEnd;
        vertex_buf_[i] = idx % 2 == 0 ? a : -a;                               // x
        vertex_buf_[i + 1u] = -a;                                             // y
        vertex_buf_[i + 2u] = idx > 1 ? -a : a;                               // z
    }
}

void CubeGeometry::setColor()
{
    std::fill(color_buf_.begin(), color_buf_.end(), 255);
}
