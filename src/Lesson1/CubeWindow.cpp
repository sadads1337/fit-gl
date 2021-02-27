#include "CubeWindow.h"

#include <QOpenGLFunctions>
#include <QScreen>
#include <array>
#include <QMouseEvent>
#include <QColorDialog>

namespace {
    struct VertexData {
        QVector3D position;
        QVector3D color;
    };

    VertexData vertices[] = {

            {QVector3D(-0.5f,  -0.5f, 0.5f), QVector3D(1.0f, 1.0f, 0.0f)},  // v0
            {QVector3D( 0.5f, -0.5f, 0.5f), QVector3D(0.0f, 0.0f, 1.0f)}, // v1
            {QVector3D(-0.5f,  0.5f,  0.5f), QVector3D(1.0f, 0.0f, 1.0f)},  // v2
            {QVector3D( 0.5f, 0.5f, 0.5f), QVector3D(1.0f, 1.0f, 0.0f)}, // v3
            {QVector3D( 0.5f,   -0.5f, -0.5f), QVector3D(0.0f, 1.0f, 1.0f)},  // v4
            {QVector3D( 0.5f, 0.5f, -0.5f), QVector3D(1.0f, 0.0f, 0.0f)}, // v5
            {QVector3D( -0.5f,  -0.5f, -0.5f), QVector3D(0.0f, 1.0f, 0.0f)},// v6
            {QVector3D( -0.5f,   0.5f, -0.5f), QVector3D(1.0f, 1.0f, 1.0f)} // v7

    };

    constexpr std::array<GLuint ,34u> indices = {
            0,  1,  2,  3,  3,
            1,  1,  4,  3,  5,  5,
            4,  4,  6, 5, 7, 7,
            6, 6, 0, 7, 2, 2,
            6, 6, 4, 0, 1, 1,
            2, 2, 3, 7, 5
    };
}

namespace fgl {

    void CubeWindow::init() {
        program_ = std::make_unique<QOpenGLShaderProgram>(this);
        program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/Shaders/triangle.vs");
        program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/Shaders/triangle.fs");
        program_->link();
        posAttr_ = program_->attributeLocation("posAttr");
        assert(posAttr_ != -1);
        colAttr_ = program_->attributeLocation("colAttr");
        assert(colAttr_ != -1);
        matrixUniform_ = program_->uniformLocation("matrix");
        assert(matrixUniform_ != -1);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    void CubeWindow::render() {
        const auto retinaScale = devicePixelRatio();
        glViewport(0, 0, width() * retinaScale, height() * retinaScale);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program_->bind();

        QMatrix4x4 matrix;
        matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
        matrix.translate(0, 0, -2);
        matrix.rotate(100.0 * frame_ / screen()->refreshRate(), rotationAxis);

        program_->setUniformValue(matrixUniform_, matrix);
        program_->setUniformValue("color", changeColor);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(posAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);
        glVertexAttribPointer(colAttr_, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                              reinterpret_cast<char *>(sizeof(QVector3D)));

        glEnableVertexAttribArray(posAttr_);
        glEnableVertexAttribArray(colAttr_);

//        glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(uint), indices.data(), GL_STATIC_DRAW);

        glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(colAttr_);
        glDisableVertexAttribArray(posAttr_);

        program_->release();

        ++frame_;
    }

    void CubeWindow::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Space) {
            const auto color = QColorDialog::getColor();
            changeColor = QVector4D(color.red() / 255.0, color.green() / 255.0, color.blue() / 255.0, 1);
        }
    }

    void CubeWindow::mousePressEvent(QMouseEvent *e) {
        // Save mouse press position
        mousePressPosition = QVector2D(e->localPos());
    }

    void CubeWindow::mouseReleaseEvent(QMouseEvent *e) {
        // Mouse release position - mouse press position
        QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        // Accelerate angular speed relative to the length of the mouse sweep
        qreal acc = diff.length() / 100.0;

        // Calculate new rotation axis as weighted sum
        rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

        // Increase angular speed
        angularSpeed += acc;

        rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    }

} // namespace fgl