#ifndef COUBSARMYWIDGET_H
#define COUBSARMYWIDGET_H

#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QLabel>
#include <QTime>
#include "coub.h"
#include "objectmodel.h"
#include "normals.h"
#include "object.h"
#include "sourcelight.h"
#include "colorowner.h"

class CoubsArmy : public QOpenGLWidget, protected QOpenGLFunctions
{
public:

    void initializeGL() override;
    void initLabel();
    void initMatrix(int col,int row);
    void initProgram();
    void initVaoVbo();
    void initShadersParam();
    void initObject();

    void paintGL() override;

    void setRotation(std::vector<GLfloat> rt);
    void setPercistenceLvl(int lvl);
    void setColor(QColorDialog* cd , int active);
    void setFactor(float nf);
    void setCol(int);
    void setRow(int);
    void setRotate(bool fl);
    void setLightCoefs(std::vector<int> vec);
    void setActivateLight(std::vector<bool>vec);

    void setProjectLight(QVector4D pos , QVector4D rot , float angle);
    void setDirectionLightPosition(QVector4D pos);
    void setPointLightPosition(QVector4D pos);

    int fps = 0;

    CoubsArmy(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags()):QOpenGLWidget(parent,f),label("FPS",this), timer(new QTimer(this)){}

    ~CoubsArmy(){}

private:
    QOpenGLBuffer *m_vbo = nullptr;
    QOpenGLVertexArrayObject *m_vao = nullptr;

    Object object;

    SourceLight directionLight;
    SourceLight ambientLight;
    SourceLight pointLight;
    SourceLight projectorLight;


    std::vector<ObjectModel> matrix;

    LightFactors coefs;

    ColorOwner colorOwner;

    int rows = 18;
    int cols = 18;

    int s_frame = 0;
    QTime time;


    QLabel label;
    QColor color;
    QColorDialog* colorDialog = nullptr;

    GLint m_norAttr = 0;
    GLint m_posAttr = 0;

    GLint m_trMatrix =0;
    GLint m_matrixUniform = 0;

    QOpenGLFunctions *f = nullptr;
    QOpenGLShaderProgram *m_program = nullptr;
    int m_frame = 0;
    QTimer* timer = nullptr;
};

#endif // COUBSARMYWIDGET_H
