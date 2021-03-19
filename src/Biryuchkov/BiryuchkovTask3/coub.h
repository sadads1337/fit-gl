#ifndef COUB_H
#define COUB_H

#include <QOpenGLShaderProgram>
#include <vector>

class Coub
{
public:
    Coub();
    std::vector<GLfloat> getVertex();
    std::vector<GLfloat> getNormals();

    size_t vertexCount();

    void setStep(GLfloat stp);
private:
    enum types {X,Y,Z};
    std::vector<GLfloat> vert ={};
    std::vector<GLfloat> norm ={};

    GLfloat step = 2.0f;

    void normals(types type , int size, bool inv);
    std::vector<GLfloat> side();
    std::vector<GLfloat> slideSide(types type);
    std::vector<GLfloat> coubVertex();
};

#endif // COUB_H
