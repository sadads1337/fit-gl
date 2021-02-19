#ifndef PLAINOBJECT3D_H
#define PLAINOBJECT3D_H

#include <QOpenGLFunctions>
#include <QColor>
#include <QOpenGLShaderProgram>

class PlainObject3D : protected QOpenGLFunctions
{
public:
    PlainObject3D() = default;

    void initialize();
    void render(QOpenGLShaderProgram* program);

    virtual void setColor(const QColor& color) = 0;

protected:
    bool is_init_ = false;

    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> colors_;

    GLuint verticesCount;

    virtual void setVertices() = 0;
    virtual void drawArrays() = 0;
};

#endif // PLAINOBJECT3D_H
