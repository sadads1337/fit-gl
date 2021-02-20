#include "plainobject3d.h"


void PlainObject3D::initialize()
{
    setVertices();
}


void PlainObject3D::render(std::shared_ptr<QOpenGLShaderProgram>& program)
{
    if(!is_init_) {
        initializeOpenGLFunctions();
        is_init_ = true;
    }

    auto m_posAttr = program->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    auto m_colAttr = program->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);


    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices_.data());
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors_.data());

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    drawArrays();

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

}
