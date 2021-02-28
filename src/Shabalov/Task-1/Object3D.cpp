//
// Created by nikita on 21.02.2021.
//

#include "Object3D.h"
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

Object3D::Object3D():
        m_indexBuffer(QOpenGLBuffer::IndexBuffer), m_texture(0)
{
    m_scale = 1.0f;
}

Object3D::Object3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, QImage texture):
        m_indexBuffer(QOpenGLBuffer::IndexBuffer), m_texture(0)
{
    m_scale = 1.0f;
    init(vertData, indexes, texture);
}

Object3D::~Object3D()
{
    if(m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if(m_indexBuffer.isCreated())
        m_indexBuffer.destroy();
    if(m_texture != 0)
    {
        if(m_texture->isCreated())
            m_texture->destroy();
    }
}

void Object3D::init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage texture)
{
    if(m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();
    if(m_indexBuffer.isCreated())
        m_indexBuffer.destroy();
    if(m_texture != 0)
    {
        if(m_texture->isCreated()){
            delete m_texture;
            m_texture = 0;
        }
    }

    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(vertData.constData(), vertData.size()*sizeof(VertexData));
    m_vertexBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(), indexes.size()*sizeof(GLuint));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(texture.mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Object3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions) {
    if (!m_vertexBuffer.isCreated() || !m_indexBuffer.isCreated()) return;
    m_texture->bind(0);
    program->setUniformValue("u_texture", 0);
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(m_translate);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);
    modelMatrix = m_globalTransform * modelMatrix;

    program->setUniformValue("u_modelMatrix", modelMatrix);

    m_vertexBuffer.bind();

    int offset = 0;

    int vertLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(vertLoc);
    program->setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texLoc = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texLoc);
    program->setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normLoc = program->attributeLocation("a_normal");
    program->enableAttributeArray(normLoc);
    program->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    m_indexBuffer.bind();

    functions->glDrawElements(GL_TRIANGLES, m_indexBuffer.size(), GL_UNSIGNED_INT, 0);

    m_vertexBuffer.release();
    m_indexBuffer.release();
    m_texture->release();
}

void Object3D::rotate(const QQuaternion &r)
{
    m_rotate = r * m_rotate;
}

void Object3D::translate(const QVector3D &t)
{
    m_translate += t;
}

