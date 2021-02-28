#pragma once

#include <Base/GLWindow.hpp>

#include <QOpenGLShaderProgram>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <vector>
#include <QColor>


namespace fgl {

    class CubeWindow final : public GLWindow {
    public:
        void init() override;
        void render() override;

    protected:
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void keyPressEvent(QKeyEvent *event) override;

    private:

        GLint posAttr_ = 0;
        GLint colAttr_ = 0;
        GLint matrixUniform_ = 0;
        qreal angularSpeed = 0;


        std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;


        // Frame counter for animation.
        int frame_ = 0;


        QVector4D square_color ={1.0, 1.0, 1.0, 1};

        QVector2D mousePressPosition;
        QVector3D rotationAxis;
    };

} // namespace fgl
