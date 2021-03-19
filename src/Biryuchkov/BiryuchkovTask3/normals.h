#ifndef NORMALS_H
#define NORMALS_H
#include <QOpenGLShaderProgram>
#include <vector>

class Normals
{
public:
    Normals();
    void setNormal(GLfloat _x,GLfloat _y,GLfloat _z);
    void setNormal(const std::vector<GLfloat>& vec);
    const std::vector<GLfloat>& getNormal();
private:
    std::vector<GLfloat> vect={};
};

#endif // NORMALS_H
