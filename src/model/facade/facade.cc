#include "facade.h"

namespace s21 {
Facade* Facade::instance_ = nullptr;

Facade::Facade(Data& data)
    : parser_(std::make_unique<Parser>(data)),
      move_(std::make_unique<MoveStrategy>(data, affine_)),
      scale_(std::make_unique<ScaleStrategy>(data, affine_)),
      rotate_(std::make_unique<RotateStrategy>(data, affine_)) {}

Facade::~Facade() { delete instance_; }

Facade& Facade::GetInstance(Data& data) noexcept {
  if (instance_ == nullptr) instance_ = new Facade(data);
  return *instance_;
}

void Facade::Parse(const std::string& path) const noexcept {
  parser_->Parse(path);
}

void Facade::Scale(const double &value, const Action& act) const noexcept {
  scale_->Transform(value, act);
}

void Facade::Move(const double &value, const Action& act) const noexcept {
  move_->Transform(value, act);
}

void Facade::Rotate(const double &value, const Action& act) const noexcept {
  rotate_->Transform(value, act);
}
}  // namespace s21
