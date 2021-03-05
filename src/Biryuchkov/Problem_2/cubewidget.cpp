/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "cubewidget.hpp"

#include <QMouseEvent>
#include <iostream>
#include <cmath>


CubeWidget::CubeWidget(QWidget* parent)
     : QOpenGLWidget(parent)
{}

void CubeWidget::setMorphFactor(float val)
{
    morphFactor = val;
    update();
}

void CubeWidget::setColor(const QColor& color)
{
    if (mode_ == colorMode::face){
        pCube_->setFaceColor(color, currentFace_);
    }
    else{
        pCube_->setEdgeColor(color, currentFace_);
    }
}

void CubeWidget::setCurrentFace(int face)
{
    currentFace_ = face;
}

void CubeWidget::setFaceMode()
{
    mode_ = colorMode::face;
}

void CubeWidget::setEdgeMode()
{
    mode_ = colorMode::edge;
}

void CubeWidget::makeNewGrid(int grid_steps)
{
    pCube_.reset(
                new Cube(
                    grid_steps,
                    initSize,
                    initFaceColor,
                    initEdgeColor
                    )
                );
}

void CubeWidget::mousePressEvent(QMouseEvent *e)
{
    mouseLastPosition = mousePressPosition = QVector2D(e->pos());
    if (e->button() == Qt::RightButton){
        angularSpeed = 0;
    }
}

void CubeWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton){
        QVector2D diff = QVector2D(e->pos()) - mousePressPosition;
        QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        qreal acc = diff.length() / 100.0;

        rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
        angularSpeed += acc;
    }
}

void CubeWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::RightButton){
        QVector2D diff = QVector2D(event->pos()) - mouseLastPosition;
        rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        qreal angle = diff.length() / 8.0;
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
    }
    mouseLastPosition = QVector2D(event->pos());
}

void CubeWidget::wheelEvent(QWheelEvent* ev)
{
    auto angle = ev->angleDelta().y();

    projection.translate(0.f, 0.f, angle / (8. * 50.));
}

void CubeWidget::timerEvent(QTimerEvent *)
{
    angularSpeed *= 0.99;
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    }
    else {
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
    update();
}

QSize CubeWidget::minimumSizeHint() const
{
    return {640, 480};
}

void CubeWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.9, 0.9, 0.9, 1);
    initShaders();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    pCube_.reset(new Cube(
                         initSteps,
                         initSize,
                         initFaceColor,
                         initEdgeColor
                         ));
    timer.start(16, this);
}

void CubeWidget::initShaders()
{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl")){
        close();
    }
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl")){
        close();
    }
    if (!program.link()){
        close();
    }
    if (!program.bind()){
        close();
    }
}

void CubeWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 100., fov = 60.;

    projection.setToIdentity();
    projection.perspective(fov, aspect, zNear, zFar);
}

void CubeWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, zDistance);
    matrix.rotate(rotation);

    program.setUniformValue("mvp_matrix", projection * matrix);
    program.setUniformValue("morphFactor", morphFactor);

    pCube_->draw(program);
}
