#include <QWindow>
#include <QOpenGLFunctions>
#include <memory>
#include <QOpenGLPaintDevice>
#include <QOpenGLContext>

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class MyMainWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyMainWindow(QWindow *parent = nullptr);

    virtual void render(const QPainter &painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating = false);

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event) override;

    void exposeEvent(QExposeEvent *event) override;

private:
    bool m_animating = false;

    std::unique_ptr<QOpenGLContext> context_ = nullptr;
    std::unique_ptr<QOpenGLPaintDevice> device_ = nullptr;
};
