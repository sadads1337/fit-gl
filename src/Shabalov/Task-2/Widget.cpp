#include "Widget.h"
#include "Object3D.h"
#include <QOpenGLContext>
#include <QtMath>

Widget::Widget(QWidget *parent)
        :QOpenGLWidget(parent)
{
    m_z = -5.0f;
    m_t = 0.0f;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;
    angleObject = (float)M_PI / 1.0f;
}

Widget::~Widget() = default;

void Widget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(2.0f, 10);
    m_timer.start(30, this);
}


void Widget::resizeGL(int w, int h){
    auto aspect = w / (double)h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45, aspect, 0.01f, 100.0f);
}

void Widget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(0.0, 0.0, m_z);
    viewMatrix.rotate(m_rotation);

    m_program.bind();
    m_program.setUniformValue("u_projectionMatrix", m_projectionMatrix);
    m_program.setUniformValue("u_viewMatrix", viewMatrix);
    m_program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_program.setUniformValue("u_lightPower", 1.0f);
    m_program.setUniformValue("u_color", m_color);
    m_program.setUniformValue("u_t", m_t);

    for(auto & m_object : m_objects){
        m_object->draw(&m_program, context()->functions());
    }
}

void Widget::initShaders(){
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                           ":/shaders/vshader.vsh"))
        close();
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                           ":/shaders/fshader.fsh"))
        close();
    if (!m_program.link())
        close();
}

void Widget::initCube(float width, int N) {
    auto half_width = width / 2.0f;
    auto part_width = width / float(N - 1);
    QVector<VertexData> vertexes;
    for (auto z = -1; z <= 1; z += 2) {
        for (auto y = 0; y < N; y++) {
            for (auto x = 0; x < N; x++) {
                vertexes.append(VertexData(
                        QVector3D(z*(-half_width +  x * part_width), -half_width + y * part_width, z * half_width),
                        QVector2D(0, 0), QVector3D(0.0, 0.0, z)));
            }
        }
    }
    for (auto x = -1; x <= 1; x += 2) {
        for (auto z = 0; z < N; z++) {
            for (auto y = 0; y < N; y++) {
                vertexes.append(VertexData(
                        QVector3D(x * half_width, -half_width + y * part_width, x*(-half_width + z * part_width)),
                        QVector2D(0, 0), QVector3D(x, 0.0, 0.0)));
            }
        }
    }
    for (auto y = -1; y <= 1; y += 2) {
        for (auto x = 0; x < N; x++) {
            for (auto z = 0; z < N; z++) {
                vertexes.append(VertexData(
                        QVector3D(-half_width + x * part_width, y * half_width, y*(-half_width + z * part_width)),
                        QVector2D(0, 0), QVector3D(0.0, y, 0.0)));
            }
        }
    }

    QVector<GLuint> indexes;
    for (int i = 0; i < 6 * N * N; i += N * N) {
        for (int j = 0; j < (N-1) * (N-1); j += N) {
            for (int k = 0; k < (N - 1); k++) {
                indexes.append(i + j + k + N);
                indexes.append(i + j + k + 0);
                indexes.append(i + j + k + N + 1);
                indexes.append(i + j + k + N + 1);
                indexes.append(i + j + k + 0);
                indexes.append(i + j + k + 1);
            }
        }
    }

    m_objects.append(std::make_shared<Object3D>(vertexes, indexes,
                                                QImage(":/textures/cube.jpg")));

}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        m_mousePosition = QVector2D(event->localPos());
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() != Qt::LeftButton)
        return;
    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    auto angle = diff.length() / 2.0;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
    update();
}

void Widget::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().x() > 0){
        m_z += 0.25f;
    } else if(event->angleDelta().x() < 0){
        m_z -=0.25f;
    }
    update();
}

void Widget::timerEvent(QTimerEvent *){
    for(int i = 0; i < m_objects.size(); i++){
        if(i % 2 == 0){
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(x_rot, y_rot, z_rot, angleObject));
        }else{
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(x_rot, y_rot, z_rot, -angleObject));
        }
    }
    update();
}

void Widget::setXRotation(float angle){
    x_rot = angle / 100.0f;
    emit xRotationChanged(angle);
    update();
}

void Widget::setYRotation(float angle){
    y_rot = angle / 100.0f;
    emit yRotationChanged(angle);
    update();
}

void Widget::setZRotation(float angle){
    z_rot = angle / 100.0f;
    emit zRotationChanged(angle);
    update();
}

void Widget::setT(float value){
    m_t = value / 100.0f;
    emit TChanged(value);
    update();
}

void Widget::setColor(const QColor& color){
    m_color = color;
    emit ColorChanged(color);
    update();
}