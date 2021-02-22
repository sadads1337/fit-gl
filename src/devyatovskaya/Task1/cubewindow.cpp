#include "cubewindow.h"
#include <QMouseEvent>


static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";


void CubeWindow::init()
{
    m_program = std::make_shared<QOpenGLShaderProgram>(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();

    m_matrixUniform = m_program->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);

    cube.initialize();
    edges.initialize();

    c_dialog.setOptions(QColorDialog::NoButtons);
    c_dialog.setVisible(1);
}


void CubeWindow::mousePressEvent(QMouseEvent *e)
{
    mousePressPosition = QVector2D(e->localPos());
}


void CubeWindow::mouseReleaseEvent(QMouseEvent *e)
{
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();       /* Rotation axis is perpendicular to the mouse position difference vector */

    qreal acc = diff.length() / 100.0;                                   /* Accelerate angular speed relative to the length of the mouse sweep */

    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized(); /* Calculate new rotation axis as weighted sum */
    angularSpeed += acc;
}


void CubeWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);

    setRotation();
    matrix.rotate(rotation);

    m_program->setUniformValue(m_matrixUniform, matrix);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    cube.setColor(c_dialog.currentColor());

    cube.render(m_program);
    edges.render(m_program);

    m_program->release();
}


void CubeWindow::setRotation()
{
    angularSpeed *= 0.99;

    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    }
    else {
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
}
