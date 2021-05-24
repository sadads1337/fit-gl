#include "coubsArmyWidget.h"
#include <QScreen>
#include <QtGui/QOpenGLTexture>

void CoubsArmy::initializeGL()
{

  colorOwner.setSources({&ambientLight , &directionLight , &pointLight});

  ambientLight.setColor(QColor(255,0,0));

  directionLight.setPosition(QVector4D( QVector3D(1,0,0), 1 ));
  directionLight.setColor(QColor(255,0,0));
  directionLight.off();

  pointLight.setPosition(QVector4D( QVector3D(0,0,-15), 1 ));
  pointLight.setColor(QColor(255,0,0));

  initMatrix();
  setRotate(false);

  initTextures();

  initProgram();
  initShadersParam();
  initVaoVbo();

  initObject();

  m_vbo->allocate( object.vertexs.data(), object.vertexs.size() * sizeof(Vertex));

  m_program->enableAttributeArray("posAttr");
  m_program->setAttributeBuffer("posAttr", GL_FLOAT, offsetof(Vertex, vertex), 3, sizeof(Vertex));

  m_program->enableAttributeArray("norAttr");
  m_program->setAttributeBuffer("norAttr", GL_FLOAT, offsetof(Vertex, normal), 3, sizeof(Vertex));

  m_program->enableAttributeArray("texCoord");
  m_program->setAttributeBuffer("texCoord", GL_FLOAT, offsetof(Vertex, texCoord), 2, sizeof(Vertex));

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

  projection.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

  glEnable(GL_DEPTH_TEST);

  colorOwner.checkColor();

  for (auto it = matrix.begin() ; it != matrix.end() ; ++it)
  {
    auto mat = it->getMatrix();

    m_program->setUniformValue(coefs.m_ka , coefs.ka);
    m_program->setUniformValue(coefs.m_kd , coefs.kd);
    m_program->setUniformValue(coefs.m_k , coefs.k);
    m_program->setUniformValue(coefs.m_p , coefs.p);

    m_program->setUniformValue(pointLight.getFlagUniform() , pointLight.state());
    m_program->setUniformValue(pointLight.getPosUniform() , pointLight.getPosition());
    m_program->setUniformValue(pointLight.getColorUniform(), pointLight.getColor());

    m_program->setUniformValue(directionLight.getFlagUniform() , directionLight.state());
    m_program->setUniformValue(directionLight.getPosUniform() , directionLight.getPosition());
    m_program->setUniformValue(directionLight.getColorUniform(), directionLight.getColor());

    m_program->setUniformValue(ambientLight.getColorUniform() , ambientLight.getColor());
    m_program->setUniformValue(ambientLight.getFlagUniform() , ambientLight.state());

    m_program->setUniformValue(m_trMatrix , mat);



    m_program->setUniformValue("textureMap",0);
    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    m_program->setUniformValue("normalMap",1);
    glActiveTexture(GL_TEXTURE1);
    normalMap->bind();

    m_program->setUniformValue(m_matrixUniform, projection*mat);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, object.vertexs.size());

  }

  m_program->release();
  ++m_frame;

}

void CoubsArmy::initTextures()
{
  texture.reset(new QOpenGLTexture(QImage(":/Texture/Earth_Albedo.jpg")));
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);

  normalMap.reset(new QOpenGLTexture(QImage(":/Texture/Earth_NormalMap.jpg")));
}

void CoubsArmy::initProgram()
{
  initializeOpenGLFunctions();
  f = QOpenGLContext::currentContext()->functions();
  m_program = new QOpenGLShaderProgram(this);
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/vertexShaider.vs");
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/fragmentShaider.fs");
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
void CoubsArmy::initMatrix()
{
  matrix.clear();

  ObjectModel objm;
  objm.setTranslate(0, 0.0f, -2.5f);
  objm.setRotate(screen()->refreshRate()/100,0.0f,1.0f,0.0f);
  matrix.push_back(objm);
}

void CoubsArmy::initShadersParam()
{
  m_posAttr = m_program->attributeLocation("posAttr");
  // Q_ASSERT(m_posAttr != -1);
  m_norAttr = m_program->attributeLocation("norAttr");
  //Q_ASSERT(m_matrixUniform != -1);

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
  // Q_ASSERT(coefs.m_p != -1);

  pointLight.setPosUniform( m_program->uniformLocation("pointPos"));
  // Q_ASSERT(pointLight.getPosUniform()  != -1);
  pointLight.setColorUniform( m_program->uniformLocation("pointColor"));
  // Q_ASSERT(pointLight.getColorUniform() != -1);
  pointLight.setFlagUniform( m_program->uniformLocation("pointFlag"));
  // Q_ASSERT(pointLight.getFlagUniform()  != -1);

  directionLight.setPosUniform( m_program->uniformLocation("directionPos"));
  // Q_ASSERT(directionLight.getPosUniform()  != -1);
  directionLight.setColorUniform( m_program->uniformLocation("directionColor"));
  // Q_ASSERT(directionLight.getColorUniform() != -1);
  directionLight.setFlagUniform( m_program->uniformLocation("directionFlag"));
  // Q_ASSERT(directionLight.getFlagUniform()  != -1);

  ambientLight.setColorUniform( m_program->uniformLocation("ambientColor"));
  //Q_ASSERT(ambientLight.getColorUniform() != -1);
  ambientLight.setFlagUniform( m_program->uniformLocation("ambientFlag"));
  //Q_ASSERT(ambientLight.getFlagUniform()  != -1);


}
void CoubsArmy::initObject()
{
  Sphere s(30,30);
  object.setObject(s.getVertex() , s.getNormals(),s.getTexCoord());
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

void CoubsArmy::setSphere(float x, float y)
{
  m_vbo->bind();
  Sphere s(x,y);
  object.setObject(s.getVertex() , s.getNormals(),s.getTexCoord());
  m_vbo->allocate( object.vertexs.data(), object.vertexs.size() * sizeof(Vertex));
  m_vbo->release();
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
}
void CoubsArmy::setActivateLight(std::vector<bool> vec)
{
  directionLight.setState(vec[0]);
  pointLight.setState(vec[1]);
}
void CoubsArmy::setDirectionLightPosition(QVector4D pos)
{
  directionLight.setPosition(pos);
}
void CoubsArmy::setPointLightPosition(QVector4D pos)
{
  pointLight.setPosition(pos);
}

