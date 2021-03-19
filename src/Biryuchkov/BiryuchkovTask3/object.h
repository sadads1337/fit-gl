#ifndef OBJECT_H
#define OBJECT_H
#include <QOpenGLShaderProgram>
#include <vector>
#include "objectmodel.h"

class Object
{
public:
    Object();
    Object(const std::vector<GLfloat>& vert ,const std::vector<GLfloat>& norms ):vertex(vert) , normal(norms){};

    void setObject(const std::vector<GLfloat>& vert ,const std::vector<GLfloat>& norms );

    const std::vector<GLfloat>& getVertex();
    const std::vector<GLfloat>& getNormals();

    std::vector<GLfloat> getData();
private:
    std::vector<GLfloat> vertex;
    std::vector<GLfloat> normal;
};

#endif // OBJECT_H
