#pragma once

#include <Base/GLWindow.hpp>

#include <QOpenGLShaderProgram>
#include <QColorDialog>
#include <QColor>

#include <QKeyEvent>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>



namespace fgl {

    class SquareWindow final : public GLWindow{

    public:
        void init() override;
        void render() override;


    protected:
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:
        // Attributes and uniforms handlers.
        GLint posAttr_ = 0;
        GLint matrixUniform_ = 0;

        // Shader program handler.
        std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;
        //color
        QVector4D square_color {1.0, 1.0, 1.0, 1};
        // Frame counter for animation.
        int frame_ = 0;

       //animation
        QVector2D mousePressPosition;
        QVector3D rotationAxis;
    };

} // namespace fgl
