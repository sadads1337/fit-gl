#include "sourcelight.h"

SourceLight::SourceLight()
{

}
void SourceLight::setState(float fl)
{
  isOn = fl;
}
void SourceLight::setPosition(QVector4D position)
{
  pos = position;
}
void SourceLight::setColor(QColor col)
{
  color = col;
}
void SourceLight::on()
{
  isOn = 1;
}
void SourceLight::off()
{
  isOn = 0;
}

const QVector4D& SourceLight::getPosition()
{
  return pos;
}
const QColor& SourceLight::getColor()
{
  return color;
}
float SourceLight::state()
{
  return isOn;
}

void SourceLight::setColorUniform(GLint clu)
{
  m_ColorUniform = clu;
}
void SourceLight::setPosUniform(GLint lig)
{
  m_PosUniform =lig;
}
void SourceLight::setFlagUniform(GLint fl)
{
  m_FlagUniform = fl;
}

GLint SourceLight::getColorUniform()
{
  return m_ColorUniform;
}
GLint SourceLight::getPosUniform()
{
  return m_PosUniform;
}
GLint SourceLight::getFlagUniform()
{
  return m_FlagUniform;
}

GLint SourceLight::getRotationUniform()
{
  return m_Rotation;
}
GLint SourceLight::getAngleUniform()
{
  return m_Angle;
}
void SourceLight::setRotationUniform(GLint rt)
{
  m_Rotation = rt;
}
void SourceLight::setAngleUniform(GLint an)
{
  m_Angle = an;
}
const QVector4D& SourceLight::getRotation()
{
  return rotation;
}
float SourceLight::getAngle()
{
  return angle;
}
void SourceLight::setRotation(QVector4D v)
{
  rotation = v;
}
void SourceLight::setAngle(float an)
{
  angle = an;
}

LightFactors::LightFactors()
{

}
