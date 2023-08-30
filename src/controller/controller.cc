#include "controller.h"

namespace s21 {
Controller::Controller(Data &data) : facade_(Facade::GetInstance(data)) {}

void Controller::Parse(const std::string &path) const { facade_.Parse(path); }

void Controller::Scale(const double &value, const Action &act) const noexcept {
  facade_.Scale(value, act);
}

void Controller::Move(const double &value, const Action &act) const noexcept {
  facade_.Move(value, act);
}

void Controller::Rotate(const double &value, const Action &act) const noexcept {
  facade_.Rotate(value, act);
}
}  // namespace s21
