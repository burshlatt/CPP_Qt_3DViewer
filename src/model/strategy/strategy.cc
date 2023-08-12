#include "strategy.h"

namespace s21 {
// ======================================= S C A L E ======================================= //
ScaleStrategy::ScaleStrategy(Data &data, Affine &affine) : data_(data), affine_(affine) {}

void ScaleStrategy::Transform(const Action &act, const double &value) {
    value_ = value;
    Scale(act);
}

void ScaleStrategy::Scale(const Action &act) const noexcept {
    if (act == ScaleP)
        affine_.Scale(data_, value_, false);
    else if (act == ScaleM)
        affine_.Scale(data_, value_, true);
}

// ======================================== M O V E ======================================== //
MoveStrategy::MoveStrategy(Data &data, Affine &affine) : data_(data), affine_(affine) {}

void MoveStrategy::Transform(const Action &act, const double &value) {
    value_ = value;
    Move(act);
}

void MoveStrategy::Move(const Action &act) const noexcept {
    if (act == MoveX)
        affine_.Move(data_, value_, X);
    else if (act == MoveY)
        affine_.Move(data_, value_, Y);
    else if (act == MoveZ)
        affine_.Move(data_, value_, Z);
}

// ====================================== R O T A T E ====================================== //
RotateStrategy::RotateStrategy(Data &data, Affine &affine) : data_(data), affine_(affine) {}

void RotateStrategy::Transform(const Action &act, const double &value) {
    value_ = value;
    Rotate(act);
}

void RotateStrategy::Rotate(const Action &act) const noexcept {
    if (act == RotX)
        affine_.Rotate(data_, value_, X);
    else if (act == RotY)
        affine_.Rotate(data_, value_, Y);
    else if (act == RotZ)
        affine_.Rotate(data_, value_, Z);
}
} // namespace s21
