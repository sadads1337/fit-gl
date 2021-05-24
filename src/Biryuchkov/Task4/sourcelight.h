#ifndef SOURCELIGHT_H
#define SOURCELIGHT_H
#include <QOpenGLShaderProgram>
#include <QColor>
#include <vector>

class SourceLight
{
public:

  SourceLight();
  void setPosition(QVector4D position);
  void setColor(QColor col);
  void on();
  void off();
  void setState(float fl);
  void setRotation(QVector4D v);
  void setAngle(float an);

  const QVector4D& getPosition();
  const QColor& getColor();
  const QVector4D& getRotation();
  float getAngle();
  float state();

  void setColorUniform(GLint clu);
  void setPosUniform(GLint lig);
  void setFlagUniform(GLint fl);
  void setRotationUniform(GLint rt);
  void setAngleUniform(GLint an);

  GLint getColorUniform();
  GLint getPosUniform();
  GLint getFlagUniform();
  GLint getRotationUniform();
  GLint getAngleUniform();

private:
  QVector4D pos;
  QColor color;
  QVector4D rotation = QVector4D(0,-1,0,1);
  float angle = 3.14f/4.0f;
  float isOn = 1;

  GLint m_ColorUniform = 0;
  GLint m_PosUniform =0;
  GLint m_FlagUniform = 0;
  GLint m_Rotation = 0;
  GLint m_Angle =0;
};

class LightFactors
{
public:
  LightFactors();

  GLint m_ka =0;
  GLint m_kd =0;
  GLint m_ks =0;
  GLint m_n =0;
  GLint m_k =0;
  GLint m_p =0;

  float ka = 0;
  float kd = 1;
  float ks = 0;
  int n = 0;
  float k = 0.8f;
  int p = 2;
};

#endif // SOURCELIGHT_H
