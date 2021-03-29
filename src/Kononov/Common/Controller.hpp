#pragma once

namespace Kononov {

class Controller {
public:
  Controller() = default;
  Controller(const Controller &) = default;
  Controller(Controller &&) noexcept = default;
  virtual ~Controller() = default;
  Controller &operator=(const Controller &) = default;
  Controller &operator=(Controller &&) noexcept = default;

  virtual void update(float delta) = 0;
};

} // namespace Kononov
