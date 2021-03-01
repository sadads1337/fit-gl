//
// Created by nikita on 21.02.2021.
//

#ifndef TASK_1_OBJECT3D_H
#define TASK_1_OBJECT3D_H


#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QVector2D>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <memory>

struct VertexData{

    VertexData(QVector3D p, QVector2D t, QVector3D n):
            position(p), texCoord(t), normal(n)
    {

    }
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

class Object3D {

public:
    Object3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage& texture);
    void init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage& texture);
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);

private:
    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;
    std::unique_ptr<QOpenGLTexture> m_texture;
    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;
    QMatrix4x4 m_globalTransform;
};


#endif //TASK_1_OBJECT3D_H
