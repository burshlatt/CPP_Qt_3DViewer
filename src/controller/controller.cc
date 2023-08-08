#include "controller.h"

namespace s21 {
Controller::Controller(Data &data) {
    facade_ = new Facade(data);
}

Controller::~Controller() {
    delete facade_;
}

void Controller::Parse(const std::string &path) noexcept {
    facade_->Parse(path);
}

void Controller::Scale(const double &value, const bool &div) const noexcept {
    facade_->Scale(value, div);
}

void Controller::Move(const double &value, const Action &act) const noexcept {
    facade_->Move(value, act);
}

void Controller::Rotate(const double &value, const Action &act) const noexcept {
    facade_->Rotate(value, act);
}
}
