#include "mymainwindow.h"

#include <QPainter>
#include <cassert>

MyMainWindow::MyMainWindow(QWindow *parent)
    : QWindow(parent)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

void MyMainWindow::render(const QPainter &) {}

void MyMainWindow::initialize(){}

void MyMainWindow::render()
{
    if (!device_) {
        device_ = std::make_unique<QOpenGLPaintDevice>(size());
      }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    const auto pixelRatio = devicePixelRatio();
    device_->setSize(size() * pixelRatio);
    device_->setDevicePixelRatio(pixelRatio);

    const QPainter painter{device_.get()};
    render(painter);
}

void MyMainWindow::renderLater()
{
    requestUpdate();
}

bool MyMainWindow::event(QEvent *event)
{
    assert(event);
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void MyMainWindow::exposeEvent(QExposeEvent *)
{
    if (isExposed())
        renderNow();
}

void MyMainWindow::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!context_) {
        context_ = std::make_unique<QOpenGLContext>(this);
        context_->setFormat(requestedFormat());
        context_->create();

        needsInitialize = true;
      }

    const auto contextBindSuccess = context_->makeCurrent(this);
     if (!contextBindSuccess) {
       return;
     }

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

     context_->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void MyMainWindow::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}
