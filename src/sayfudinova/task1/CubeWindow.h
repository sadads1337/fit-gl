#ifndef CUBE_CUBEWINDOW_H
#define CUBE_CUBEWINDOW_H

#include <Base/GLWindow.hpp>
#include <memory>
#include <QOpenGLShaderProgram>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>

namespace fgl {

    class CubeWindow final : public GLWindow {
        Q_OBJECT
    public:
        void init() override;
        void render() override;

    protected:
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void keyPressEvent(QKeyEvent *e) override;

    private:
        // Attributes and uniforms handlers.
        GLint posAttr_ = 0;
        GLint colAttr_ = 0;
        GLint matrixUniform_ = 0;

        // Shader program handler.
        std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

        // Frame counter for animation.
        int frame_ = 0;

        QVector4D changeColor {1.0, 1.0,   1.0, 1};
        QVector2D mousePressPosition;
        QVector3D rotationAxis;
        qreal angularSpeed = 0;
    };

} // namespace fgl
#endif //CUBE_CUBEWINDOW_H
