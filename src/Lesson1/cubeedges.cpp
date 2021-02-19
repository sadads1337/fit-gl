#include "cubeedges.h"

void CubeEdges::setVertices()
{
    GLfloat a = edgeLen_ / 2;
    unsigned dim = 3;

    for (unsigned i = 0; i < 8 * dim; i += dim){                           /* frirst 8 */
        auto idx = static_cast<int>(i / dim);
        vertices_[i]     = idx % 7 == 0
                        ||(idx > 2 && idx < 5) ? -a : a;                   // x
        vertices_[i + 1] = idx > 1 && idx < 6 ? -a : a;                    // y
        vertices_[i + 2] = idx > 3 ? -a : a;                               // z
    }

    for (unsigned i = 8 * dim; i < 16 * dim; i += dim){                    /* last 8 */
        auto idx = static_cast<int>(i / dim) - 8;
        vertices_[i]     = idx > 3 ? a : -a;                               // x
        vertices_[i + 1] = idx > 1 && idx < 6 ? -a : a;                    // y
        vertices_[i + 2] = (idx > 0 && idx < 3)
                         ||(idx > 4 && idx < 7) ? -a : a;                  // z
    }
}


void CubeEdges::setColor(const QColor&)
{
    for (unsigned i = 0; i < verticesCount * 3; i += 3){
        colors_[i]     = 0.0f;
        colors_[i + 1] = 0.0f;
        colors_[i + 2] = 0.0f;
    }
}

void CubeEdges::drawArrays()
{
    for (auto i = 0; i <= 12; i += 4){
        glDrawArrays(GL_LINE_LOOP, i, 4);
    }
}
