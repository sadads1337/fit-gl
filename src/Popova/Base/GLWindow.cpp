#include "GLWindow.hpp"

#include <cassert>

#include <QPainter>

namespace fgl {

GLWindow::GLWindow(QWindow *parent) : QWindow{parent} {
  // This one inits OpenGL functions.
  setSurfaceType(QWindow::OpenGLSurface);
}

void GLWindow::init() {}

void GLWindow::render() {
  // Lazy init render device.
  if (!device_) {
    device_ = std::make_unique<QOpenGLPaintDevice>(size());
  }

  // Clear all buffers.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  // Init sizes.
  const auto pixelRatio = devicePixelRatio();
  device_->setSize(size() * pixelRatio);
  device_->setDevicePixelRatio(pixelRatio);

  // Paint now.
  const QPainter painter{device_.get()};
  render(painter);
}

void GLWindow::render(const QPainter &) {}

void GLWindow::renderLater() {
  // Post message to request window surface redraw.
  requestUpdate();
}

void GLWindow::setAnimated(const bool animating) { animating_ = animating; }

void GLWindow::renderNow() {
  // If not exposed yet then skip render.
  if (!isExposed()) {
    return;
  }

  auto needsInitialize = false;

  // Lazy init gl context.
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
    init();
  }

  // Render now then swap buffers.
  render();

  context_->swapBuffers(this);

  // Post message to redraw later if animating.
  if (animating_) {
    renderLater();
  }
}

bool GLWindow::event(QEvent *event) {
  assert(event);
  switch (event->type()) {
  case QEvent::UpdateRequest:
    // In case someone requested update we render inplace.
    renderNow();
    return true;
  default:
    return QWindow::event(event);
  }
}

void GLWindow::exposeEvent(QExposeEvent *) {
  if (isExposed()) {
    renderNow();
  }
}

} // namespace fgl
