#include "facade.h"

namespace s21 {
Facade::Facade(Data &data) {
    parser_ = new Parser(data);
    move_ = new MoveStrategy(data, affine_);
    scale_ = new ScaleStrategy(data, affine_);
    rotate_ = new RotateStrategy(data, affine_);
}

Facade::~Facade() {
    delete move_;
    delete scale_;
    delete rotate_;
    delete parser_;
}

void Facade::Parse(const std::string &path) noexcept {
    parser_->Parse(path);
}

void Facade::Scale(const double &value, const bool &div) const noexcept {
    if (!div)
        scale_->Transform(ScaleP, value);
    else
        scale_->Transform(ScaleM, value);
}

void Facade::Move(const double &value, const Action &act) const noexcept {
    move_->Transform(act, value);
}

void Facade::Rotate(const double &value, const Action &act) const noexcept {
    rotate_->Transform(act, value);
}
}
