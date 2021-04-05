#pragma once

#include <QVector3D>
#include <memory>

#include "Controller.hpp"
#include "PositionedObject.hpp"

namespace Kononov {

class ConstantRotationController : public Controller {
public:
  void update(float delta) override;

  [[nodiscard]] const std::shared_ptr<PositionedObject> &getObject() const;
  void setObject(const std::shared_ptr<PositionedObject> &object);
  [[nodiscard]] float getRotationSpeed() const;
  void setRotationSpeed(float rotation_speed);
  [[nodiscard]] const QVector3D &getAxis() const;
  void setRotationAxis(const QVector3D &axis);
  [[nodiscard]] float getAngle() const;
  void setAngle(float angle);

private:
  std::shared_ptr<PositionedObject> m_object;
  float m_rotation_speed{0.0F};
  QVector3D m_axis{0.0F, 1.0F, 0.0F};
  float m_angle{0.0F};
};

} // namespace Kononov
