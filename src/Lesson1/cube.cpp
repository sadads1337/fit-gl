#include "cube.h"

void Cube::setVertices()
{
    GLfloat a = edgeLen_ / 2;
    unsigned dim = 3;
    unsigned sideSurfCount = 10, topCount = 4, bottomCount = 4;

    Q_ASSERT(sideSurfCount + topCount + bottomCount == verticesCount);

    for (unsigned i = 0; i < sideSurfCount * dim; i += dim){               /* side surface vertices */
        auto idx = static_cast<int>(i / dim);
        vertices_[i]     = idx > 1 && idx < 6 ? a : -a;                    // x
        vertices_[i + 1] = idx % 2 == 0 ? a : -a;                          // y
        vertices_[i + 2] = idx > 3 && idx < 8 ? -a : a;                    // z
    }

    auto topIdxEnd = topCount + sideSurfCount;
    for (unsigned i = sideSurfCount * dim; i < topIdxEnd * dim; i += dim){ /* top vertices */
        auto idx = static_cast<int>(i / dim) - sideSurfCount;
        vertices_[i]     = idx % 2 == 0 ? -a : a;                          // x
        vertices_[i + 1] = a;                                              // y
        vertices_[i + 2] = idx > 1 ? -a : a;                               // z
    }

    auto bottomIdxEnd = topIdxEnd + bottomCount;
    for (unsigned i = topIdxEnd * dim; i < bottomIdxEnd * dim; i += dim) { /* bottom vertices */
        auto idx = static_cast<int>(i / dim) - topIdxEnd;
        vertices_[i]     = idx % 2 == 0 ? a : -a;                          // x
        vertices_[i + 1] = -a;                                             // y
        vertices_[i + 2] = idx > 1 ? -a : a;                               // z
    }
}


void Cube::setColor(const QColor& color)
{
    for (unsigned i = 0; i < colors_.size(); i += 3){
        auto coefficient = 0.05;
        coefficient = i % 3 == 0 ? coefficient / 10 : coefficient;

        colors_[i]     = color.redF() - i * coefficient;
        colors_[i + 1] = color.greenF() - i * coefficient;
        colors_[i + 2] = color.blueF() - i * coefficient;
    }
}


void Cube::drawArrays()
{
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);
    glDrawArrays(GL_TRIANGLE_STRIP, 10, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 14, 4);
}
