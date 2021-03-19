#include "coubsArmyWidget.h"
#include <QScreen>


void CoubsArmy::initializeGL()
{
    time = QTime::currentTime();

    colorOwner.setSources({&ambientLight , &directionLight , &pointLight , &projectorLight});

    ambientLight.setColor(QColor(255,0,0));

    directionLight.setPosition(QVector4D( QVector3D(1,0,0), 1 ));
    directionLight.setColor(QColor(255,0,0));
    directionLight.off();

    pointLight.setPosition(QVector4D( QVector3D(0,0,-15), 1 ));
    pointLight.setColor(QColor(255,0,0));

    projectorLight.setColor(QColor(255,0,0));
    projectorLight.setPosition(QVector4D( QVector3D(0,10,-30), 1 ));

    initLabel();
    initMatrix(cols,rows);
    setRotate(false);

    initProgram();
    initShadersParam();
    initVaoVbo();

    initObject();

    m_vbo->allocate( &object.getData()[0], object.getData().size() * sizeof(GLfloat));

    f->glEnableVertexAttribArray(m_posAttr);
    f->glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, (3 +3) * sizeof(GLfloat),
                             nullptr);

    f->glEnableVertexAttribArray(m_norAttr);
    f->glVertexAttribPointer(m_norAttr, 3, GL_FLOAT, GL_FALSE, (3 +3) * sizeof(GLfloat),
                             reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    m_vbo->release();
}
void CoubsArmy::paintGL()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    m_vao->bind();
    m_program->bind();

    QMatrix4x4 projection;

    projection.perspective(100.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    colorOwner.checkColor();

    for (auto it = matrix.begin() ; it != matrix.end() ; ++it)
    {
        auto mat = it->getMatrix();

        m_program->setUniformValue(coefs.m_ka , coefs.ka);
        m_program->setUniformValue(coefs.m_kd , coefs.kd);
        m_program->setUniformValue(coefs.m_k , coefs.k);
        m_program->setUniformValue(coefs.m_p , coefs.p);
        m_program->setUniformValue(coefs.m_ks , coefs.ks);
        m_program->setUniformValue(coefs.m_n , coefs.n);


        m_program->setUniformValue(pointLight.getFlagUniform() , pointLight.state());
        m_program->setUniformValue(pointLight.getPosUniform() , pointLight.getPosition());
        m_program->setUniformValue(pointLight.getColorUniform(), pointLight.getColor());

        m_program->setUniformValue(projectorLight.getFlagUniform() , projectorLight.state());
        m_program->setUniformValue(projectorLight.getPosUniform() , projectorLight.getPosition());
        m_program->setUniformValue(projectorLight.getColorUniform(), projectorLight.getColor());
        m_program->setUniformValue(projectorLight.getRotationUniform() , projectorLight.getRotation());
        m_program->setUniformValue(projectorLight.getAngleUniform(), projectorLight.getAngle());

        m_program->setUniformValue(directionLight.getFlagUniform() , directionLight.state());
        m_program->setUniformValue(directionLight.getPosUniform() , directionLight.getPosition());
        m_program->setUniformValue(directionLight.getColorUniform(), directionLight.getColor());

        m_program->setUniformValue(ambientLight.getColorUniform() , ambientLight.getColor());
        m_program->setUniformValue(ambientLight.getFlagUniform() , ambientLight.state());

        m_program->setUniformValue(m_trMatrix , mat);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDrawArrays(GL_TRIANGLES, 0, object.getVertex().size()/3);

        m_program->setUniformValue(m_matrixUniform, projection*mat);
    }

    m_program->release();
    ++m_frame;

    if (time.msecsTo(QTime::currentTime()) > 1000)
    {
        label.setText(" FPS: " + QString::number((m_frame - s_frame) / time.secsTo(QTime::currentTime())));
        time = QTime::currentTime();
        s_frame = m_frame;

    }

}

void CoubsArmy::initProgram()
{
    initializeOpenGLFunctions();
    f = QOpenGLContext::currentContext()->functions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vertexShaider.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fragmentShaider.glsl");
    m_program->link();
    m_program->bind();
}
void CoubsArmy::initVaoVbo()
{
    m_vao = new QOpenGLVertexArrayObject;
    if (m_vao->create())
        m_vao->bind();

    m_vbo = new QOpenGLBuffer;
    m_vbo->create();
    m_vbo->bind();
}
void CoubsArmy::initMatrix(int col,int row)
{
    matrix.clear();
    cols = col;
    rows = row;

    for (int i = 0 ; i< row ; i++ )
    {
        for (int k = -col ; k< col ; k++ )
        {
            ObjectModel objm;
            objm.setTranslate(k*3+3.0f, -6.0f, -6.0f - i*3);
            objm.setRotate(screen()->refreshRate()/100,0,1.0f,0);
            matrix.push_back(objm);
        }
    }

}
void CoubsArmy::initLabel()
{
    label.setStyleSheet("QLabel { background-color : white; color : black; }");
    label.setStyleSheet("QLabel { font-size : 20px}");
    label.setGeometry(10,10,90,30);
    label.setAutoFillBackground(true);
    //label.show();
}
void CoubsArmy::initShadersParam()
{
    m_posAttr = m_program->attributeLocation("posAttr");
    //Q_ASSERT(m_posAttr != -1);
    m_norAttr = m_program->attributeLocation("norAttr");
    // Q_ASSERT(m_matrixUniform != -1);

    m_matrixUniform = m_program->uniformLocation("matrix");
    // Q_ASSERT(m_matrixUniform != -1);
    m_trMatrix = m_program->uniformLocation("trmatrix");
    // Q_ASSERT(m_trMatrix  != -1);

    coefs.m_ka = m_program->uniformLocation("ka");
    // Q_ASSERT(coefs.m_ka != -1);
    coefs.m_kd = m_program->uniformLocation("kd");
    // Q_ASSERT(coefs.m_kd != -1);
    coefs.m_k = m_program->uniformLocation("k");
    // Q_ASSERT(coefs.m_k != -1);
    coefs.m_p = m_program->uniformLocation("p");
    //  Q_ASSERT(coefs.m_p != -1);
    coefs.m_ks = m_program->uniformLocation("ks");
    // Q_ASSERT(coefs.m_ks != -1);
    coefs.m_n = m_program->uniformLocation("n");
    // Q_ASSERT(coefs.m_n != -1);

    pointLight.setPosUniform( m_program->uniformLocation("pointPos"));
    //Q_ASSERT(pointLight.getPosUniform()  != -1);
    pointLight.setColorUniform( m_program->uniformLocation("pointColor"));
    // Q_ASSERT(pointLight.getColorUniform() != -1);
    pointLight.setFlagUniform( m_program->uniformLocation("pointFlag"));
    // Q_ASSERT(pointLight.getFlagUniform()  != -1);

    directionLight.setPosUniform( m_program->uniformLocation("directionPos"));
    //  Q_ASSERT(directionLight.getPosUniform()  != -1);
    directionLight.setColorUniform( m_program->uniformLocation("directionColor"));
    // Q_ASSERT(directionLight.getColorUniform() != -1);
    directionLight.setFlagUniform( m_program->uniformLocation("directionFlag"));
    // Q_ASSERT(directionLight.getFlagUniform()  != -1);

    projectorLight.setPosUniform(m_program->uniformLocation("projectorPos"));
    // Q_ASSERT(projectorLight.getPosUniform()  != -1);
    projectorLight.setFlagUniform(m_program->uniformLocation("projectorFlag"));
    // Q_ASSERT(projectorLight.getFlagUniform()  != -1);
    projectorLight.setColorUniform(m_program->uniformLocation("projectorColor"));
    // Q_ASSERT(projectorLight.getColorUniform()  != -1);
    projectorLight.setAngleUniform(m_program->uniformLocation("projectorAngle"));
    // Q_ASSERT(projectorLight.getAngleUniform()  != -1);
    projectorLight.setRotationUniform(m_program->uniformLocation("projectorRot"));
    // Q_ASSERT(projectorLight.getRotationUniform()  != -1);


    ambientLight.setColorUniform( m_program->uniformLocation("ambientColor"));
    // Q_ASSERT(ambientLight.getColorUniform() != -1);
    ambientLight.setFlagUniform( m_program->uniformLocation("ambientFlag"));
    // Q_ASSERT(ambientLight.getFlagUniform()  != -1);


}
void CoubsArmy::initObject()
{
    Coub coub;
    object.setObject(coub.getVertex() , coub.getNormals());
}

void CoubsArmy::setRotation(std::vector<GLfloat> rt)
{
    for (auto it = matrix.begin() ; it!=matrix.end() ; ++it )
    {
        it->setRotate(rt[0],rt[1],rt[2]);
    }
}
void CoubsArmy::setColor(QColorDialog* cd , int active)
{
    colorOwner.setActive(active);
    colorOwner.setDialog(cd);
}
void CoubsArmy::setPercistenceLvl(int lvl)
{
    GLfloat step = static_cast<GLfloat>(2) / static_cast<GLfloat>(lvl);
    m_vbo->bind();

    Coub coub;
    coub.setStep(step);
    object.setObject(coub.getVertex() , coub.getNormals());


    m_vbo->allocate( &object.getData()[0], object.getData().size() * sizeof(GLfloat));
    m_vbo->release();

}
void CoubsArmy::setCol(int col )
{
    cols = col;
    initMatrix(cols,rows);

}
void CoubsArmy::setRow(int row)
{
    rows = row;
    initMatrix(cols,rows);
}
void CoubsArmy::setRotate(bool fl)
{
    for (auto it = matrix.begin() ; it!=matrix.end() ; ++it )
    {
        it->rotate(fl);
    }
}
void CoubsArmy::setLightCoefs(std::vector<int> vec)
{
    coefs.ka = static_cast<float>(vec[0])/100;
    coefs.kd = static_cast<float>(vec[1])/100;
    coefs.k = static_cast<float>(vec[2])/10;
    coefs.p = vec[3];
    coefs.ks = static_cast<float>(vec[4])/100;
    coefs.n = vec[5];
}
void CoubsArmy::setActivateLight(std::vector<bool> vec)
{
    directionLight.setState(vec[0]);
    pointLight.setState(vec[1]);
    projectorLight.setState(vec[2]);
}
void CoubsArmy::setDirectionLightPosition(QVector4D pos)
{
    directionLight.setPosition(pos);
}
void CoubsArmy::setPointLightPosition(QVector4D pos)
{
    pointLight.setPosition(pos);
}
void CoubsArmy::setProjectLight(QVector4D pos , QVector4D rot , float angle)
{
    projectorLight.setAngle(angle);
    projectorLight.setPosition(pos);
    projectorLight.setRotation(rot);
}
