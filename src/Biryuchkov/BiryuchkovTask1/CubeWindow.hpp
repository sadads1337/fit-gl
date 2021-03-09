#pragma once

#include <Base/GLWindow.hpp>
#include <QColor>
#include <QColorDialog>
#include <QKeyEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <memory>

namespace fgl {

    class CubeWindow final : public GLWindow {
    public:
        void init() override;
        void render() override;

    private:
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;
        void keyPressEvent(QKeyEvent *e) override;

        // Attributes and uniforms handlers.
        GLint posAttr_ = 0;
        GLint matrixUniform_ = 0;

        // Shader program handler.
        std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

        // Frame counter for animation.
        int frame_ = 0;

        QOpenGLBuffer array_buffer_;
        QOpenGLBuffer index_buffer_{QOpenGLBuffer::IndexBuffer};

        QVector4D square_color;
        QVector2D mousePressPosition;
        QVector3D rotationAxis;
    };

} // namespace fgl
