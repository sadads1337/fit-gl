#pragma once

#include <QOpenGLFunctions>
#include <QColor>
#include <QOpenGLShaderProgram>
#include <memory>



class PlainObject3D : protected QOpenGLFunctions
{
public:
    PlainObject3D() = default;

    void initialize();
    void render(std::shared_ptr<QOpenGLShaderProgram>& program);

    virtual void setColor(const QColor& color) = 0;

protected:
    bool is_init_ = false;

    std::vector<GLfloat> vertices_;
    std::vector<GLfloat> colors_;

    GLuint verticesCount;

    virtual void setVertices() = 0;
    virtual void drawArrays() = 0;
};
