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
    [[nodiscard]] const std::vector<GLfloat>& getNormal() const noexcept;
private:
    std::vector<GLfloat> vect={};
};

#endif // NORMALS_H
