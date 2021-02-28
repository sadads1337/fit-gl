//
// Created by nikita on 19.02.2021.
//

#include "Widget.h"
#include <QOpenGLContext>
#include <QtMath>
#include "Object3D.h"

Widget::Widget(QWidget *parent)
        :QOpenGLWidget(parent)
{
    m_z = -5.0f;
}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(1.0f);
    m_objects[0]->translate(QVector3D(1, 0.0, 0.0));
    initCube(1.0f);
    m_objects[1]->translate(QVector3D(-1, 0.0, 0.0));

    m_timer.start(30, this);
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (float)h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45,aspect, 0.01f, 100.0f);
}

void Widget::paintGL()
{
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

    for(int i = 0; i< m_objects.size(); i++){
        m_objects[i]->draw(&m_program, context()->functions());
    }
}

void Widget::initShaders()
{
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, "/home/nikita/CLionProjects/Task-1/vshader.vsh"))
        close();
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, "/home/nikita/CLionProjects/Task-1/fshader.fsh"))
        close();
    if(!m_program.link())
        close();
}

void Widget::initCube(float width)
{
    float half_width = width / 2.0f;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-half_width, half_width, half_width), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(-half_width, -half_width, half_width), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(half_width, half_width, half_width), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, 1.0)));
    vertexes.append(VertexData(QVector3D(half_width, -half_width, half_width), QVector2D(1.0, 0.0),QVector3D(0.0, 0.0, 1.0)));

    vertexes.append(VertexData(QVector3D(half_width, half_width, half_width), QVector2D(0.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(half_width, -half_width, half_width), QVector2D(0.0, 0.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(half_width, half_width, -half_width), QVector2D(1.0, 1.0), QVector3D(1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(half_width, -half_width, -half_width), QVector2D(1.0, 0.0),QVector3D(1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(half_width, half_width, half_width), QVector2D(0.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(half_width, half_width, -half_width), QVector2D(0.0, 0.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-half_width, half_width, half_width), QVector2D(1.0, 1.0), QVector3D(0.0, 1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-half_width, half_width, -half_width), QVector2D(1.0, 0.0),QVector3D(0.0, 1.0, 0.0)));

    vertexes.append(VertexData(QVector3D(half_width, half_width, -half_width), QVector2D(0.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(half_width, -half_width, -half_width), QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-half_width, half_width, -half_width), QVector2D(1.0, 1.0), QVector3D(0.0, 0.0, -1.0)));
    vertexes.append(VertexData(QVector3D(-half_width, -half_width, -half_width), QVector2D(1.0, 0.0),QVector3D(0.0, 0.0, -1.0)));

    vertexes.append(VertexData(QVector3D(-half_width, half_width, half_width), QVector2D(0.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-half_width, half_width, -half_width), QVector2D(0.0, 0.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-half_width, -half_width, half_width), QVector2D(1.0, 1.0), QVector3D(-1.0, 0.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-half_width, -half_width, -half_width), QVector2D(1.0, 0.0),QVector3D(-1.0, 0.0, 0.0)));

    vertexes.append(VertexData(QVector3D(-half_width, -half_width, half_width), QVector2D(0.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(-half_width, -half_width, -half_width), QVector2D(0.0, 0.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(half_width,-half_width, half_width), QVector2D(1.0, 1.0), QVector3D(0.0, -1.0, 0.0)));
    vertexes.append(VertexData(QVector3D(half_width, -half_width, -half_width), QVector2D(1.0, 0.0),QVector3D(0.0, -1.0, 0.0)));

    QVector<GLuint> indexes;
    for(int i = 0; i < 24; i+=4)
    {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

    m_objects.append(new Object3D(vertexes, indexes, QImage("/home/nikita/CLionProjects/Task-1/cube.jpg")));

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        m_mousePosition = QVector2D(event->localPos());
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() != Qt::LeftButton) return;
    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    float angle = diff.length() / 2.0;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    m_rotation = QQuaternion::fromAxisAndAngle(axis, angle) * m_rotation;
    update();
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        m_z += 0.25f;
    } else if(event->delta() < 0){
        m_z -=0.25f;
    }
    update();
}

void Widget::timerEvent(QTimerEvent *event)
{
    for(int i = 0; i < m_objects.size(); i++){
        if(i % 2 == 0){
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(x_rot, y_rot, z_rot, angleObject));
        }else{
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(x_rot, y_rot, z_rot, -angleObject));
        }
    }
    angleObject = M_PI / 1.0f;
    update();
}

void Widget::setXRotation(float angle)
{
    x_rot = angle / 100.0f;
    emit xRotationChanged(angle);
    update();
}

void Widget::setYRotation(float angle)
{
    y_rot = angle / 100.0f;
    emit yRotationChanged(angle);
    update();
}

void Widget::setZRotation(float angle)
{
    z_rot = angle / 100.0f;
    emit zRotationChanged(angle);
    update();
}

void Widget::setColor(QColor color)
{
    m_color = color;
    emit ColorChanged(color);
    update();
}
