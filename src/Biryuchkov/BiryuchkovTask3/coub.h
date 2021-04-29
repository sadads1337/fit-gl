#ifndef COUB_H
#define COUB_H

#include <QOpenGLShaderProgram>
#include <vector>

class Coub
{
public:
    Coub();
    [[nodiscard]] std::vector<GLfloat> getVertex() const noexcept;
    [[nodiscard]] std::vector<GLfloat> getNormals() const noexcept;

    [[nodiscard]] size_t vertexCount() const noexcept;

     void setStep(GLfloat stp) ;
private:
    enum types {X,Y,Z};
    std::vector<GLfloat> vert ={};
    std::vector<GLfloat> norm ={};

    GLfloat step = 2.0f;

    void normals(types type , int size, bool inv);
    [[nodiscard]] std::vector<GLfloat> side() const noexcept;
    [[nodiscard]] std::vector<GLfloat> slideSide(types type) const noexcept;
      std::vector<GLfloat> coubVertex();
};

#endif // COUB_H
