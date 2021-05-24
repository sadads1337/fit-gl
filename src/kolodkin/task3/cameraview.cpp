#include "cameraview.hpp"
#include <algorithm>
#include <cmath>

void CameraView::updateVectors() {
  front_.setX(std::cos(yaw_) * std::cos(pitch_));
  front_.setY(-std::sin(pitch_));
  front_.setZ(std::sin(yaw_) * std::cos(pitch_));
  front_.normalize();
  right_ = QVector3D::crossProduct(front_, worldUp_).normalized();
  up_ = QVector3D::crossProduct(right_, front_).normalized();
}

CameraView::CameraView(const QVector3D &eye_pos, const QVector3D &front,
                       const QVector3D &up)
    : eyePos_(eye_pos), front_(front), worldUp_(up) {
  yaw_ = std::atan2(front_.z(), front_.x());
  pitch_ = -std::asin(front_.y());
  updateVectors();
}

QMatrix4x4 const &CameraView::getViewMatrix() {
  view_.setToIdentity();
  view_.lookAt(eyePos_, eyePos_ + front_, up_);
  return view_;
}

const QMatrix4x4 &CameraView::getProjectionMatrix() {
  projection_.setToIdentity();
  projection_.perspective(fov_, aspectRatio_, zNear_, zFar_);
  return projection_;
}

const QMatrix4x4 &CameraView::getProjViewMatrix() {
  projView_ = getProjectionMatrix() * getViewMatrix();
  return projView_;
}

const QVector3D &CameraView::cameraPosition() const { return eyePos_; }

const QVector3D &CameraView::front() const { return front_; }

const QVector3D &CameraView::up() const { return up_; }

const QVector3D &CameraView::right() const { return right_; }

void CameraView::setProjection(float fov, float aspectRatio, float zNear,
                               float zFar) {
  setFOV(fov);
  setAspectRatio(aspectRatio);
  setZNear(zNear);
  setZFar(zFar);
}

void CameraView::setFOV(float fov) { fov_ = fov; }

void CameraView::setAspectRatio(float ratio) { aspectRatio_ = ratio; }

void CameraView::setZNear(float zNear) { zNear_ = zNear; }

void CameraView::setZFar(float zFar) { zFar_ = zFar; }

void CameraView::offsetMove(const QVector3D &offset) {
  eyePos_ += front_ * offset.z();
  eyePos_ += up_ * offset.y();
  eyePos_ += right_ * offset.x();
}

void CameraView::moveTo(const QVector3D &position) { eyePos_ = position; }

void CameraView::rotate(float yaw, float pitch) {
  yaw_ += yaw;
  pitch_ += pitch;

  if constexpr (constrainPitch) {
    pitch_ = std::clamp(pitch_, -static_cast<float>(M_PI) / 2.2f,
                        static_cast<float>(M_PI) / 2.2f);
  }
  updateVectors();
}
