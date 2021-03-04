#pragma once
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QColorDialog>
#include <QBasicTimer>
#include "morphingwidget.h"
#include "GLCubeMeshGenerator.h"
#include "GLCubeMeshRenderer.h"
#include <random>
#include <QRandomGenerator>

constexpr std::size_t initial_grid_step = 10;

template<class T, class dummy = std::enable_if<std::is_floating_point_v<T>>>
struct gen_float
{
    gen_float(const T min, const T max) :dist{ min, max } {}

    std::uniform_real_distribution<T> dist;
    std::mt19937 engine{ 0 };

    auto operator()() {
        return dist(engine);
    }
};



class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit CubeWidget(QWidget* parent = nullptr)
        :   QOpenGLWidget{ parent },
            morphing_widget_(*this)
    {
        connect(&color_dialog_, &QColorDialog::currentColorChanged, this, &CubeWidget::set_cube_color);
    }


public slots:
    void show_color_dialog()
    {
        color_dialog_.show();
    }
    void show_morph_dialog()
    {
        morphing_widget_.show();
    }
    void set_morph_factor(int morph_factor)
    {
        morph_factor_ = static_cast<float>(morph_factor) / 100.f;
    }
    void update_grid(size_t grid_step)
    {
        mesh_ = generator_.generate(grid_step);
        renderer_.reload();
    }
    void set_cube_color(const QColor& color)
    {
        std::for_each(mesh_.vertices.begin(), mesh_.vertices.end(), [&](GLVertex& vertex)
        {
            vertex.color = { static_cast<float>(color.redF()), static_cast<float>(color.greenF()), static_cast<float>(color.blueF())};
        });
        renderer_.reload();
    }
    void set_random_color()
    {
        std::for_each(mesh_.vertices.begin(), mesh_.vertices.end(), [&](GLVertex& vertex)
        {
            vertex.color = { random_gen_() / 2, random_gen_(), random_gen_() };
        });
        renderer_.reload();
    }

protected:

    void initializeGL() override
    {
        initializeOpenGLFunctions();

        glClearColor(0.1f, 0.3f, 0.3f, 1);

        const auto retina_scale = static_cast<GLsizei>(devicePixelRatio());
        glViewport(0, 0, width() * retina_scale, height() * retina_scale);

        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);

        mesh_ = generator_.generate(initial_grid_step);

        renderer_.init_renderer(&mesh_, ":/Shaders/vshader.vsh", ":/Shaders/fshader.fsh");

        timer_.start(16, this);
    }


    void resizeGL(const int w, const int h) override
    {
        qreal aspect = qreal(w) / qreal(h ? h : 1);
        const auto near_plane = 0.1f, far_plane = 100.0f, fov = 45.0f;

        projection_.setToIdentity();
        projection_.perspective(fov, aspect, near_plane, far_plane);
    }


    void paintGL() override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        QMatrix4x4 matrix;
        matrix.translate(0.0, 0.0, z_distance_);
        matrix.rotate(rotation_);

        glDepthFunc(GL_LESS);
        //glCullFace(GL_BACK);

        renderer_.shader_program().setUniformValue("mvp_matrix", projection_ * matrix);
        renderer_.shader_program().setUniformValue("morphFactor", morph_factor_);

        renderer_.render();
    }


    void wheelEvent(QWheelEvent* ev) override
    {
        const auto angle = ev->angleDelta().y();

        z_distance_ += static_cast<float>(angle) / (8.f * 50.f);
    }
    void mousePressEvent(QMouseEvent* e) override
    {
        mousePressPosition = QVector2D(e->localPos());
    }
    void mouseReleaseEvent(QMouseEvent* e) override
    {
        if (e->button() == Qt::LeftButton) {
            QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;
            QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
            qreal acc = diff.length() / 100.0;

            rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
            angularSpeed += acc;
        }
        else if (e->button() == Qt::RightButton) {
            angularSpeed = 0.f;

        }
    }
    void timerEvent(QTimerEvent* ev) override
    {
        angularSpeed *= 0.99;
        if (angularSpeed < 0.01) {
            angularSpeed = 0.0;
        }
        else {
            rotation_ = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation_;
        }
        update();
    }


private:
    QColorDialog color_dialog_;
    MorphingWidget morphing_widget_;

    GLMesh mesh_;
    GLCubeMeshGenerator generator_{ 1.0f};
    GLCubeMeshRenderer renderer_;

    float morph_factor_{ 0 };


    QMatrix4x4 projection_;
    QQuaternion rotation_;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed = 0;

    float z_distance_{ -6 };
    QBasicTimer timer_;

    gen_float<float> random_gen_{ 0.f, 1.f };
};
