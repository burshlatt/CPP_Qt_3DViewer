#include "strategy.h"

namespace s21 {
// ======================================= S C A L E ======================================= //
ScaleStrategy::ScaleStrategy(Data &data, Affine &affine) : data_(data), affine_(affine) {}

void ScaleStrategy::Transform(const Action &act, const double &value) {
    value_ = value;
    if (act == ScaleP)
        ScalePlus();
    else if (act == ScaleM)
        ScaleMinus();
}

void ScaleStrategy::ScalePlus() {
    affine_.Scale(data_, value_, false);
}

void ScaleStrategy::ScaleMinus() {
    affine_.Scale(data_, value_, true);
}

// ======================================== M O V E ======================================== //
MoveStrategy::MoveStrategy(Data &data, Affine &affine) : data_(data), affine_(affine) {}

void MoveStrategy::Transform(const Action &act, const double &value) {
    value_ = value;
    if (act == MoveX)
        MoveXCoord();
    else if (act == MoveY)
        MoveYCoord();
    else if (act == MoveZ)
        MoveZCoord();
}

void MoveStrategy::MoveXCoord() {
    affine_.Move(data_, value_, X);
}

void MoveStrategy::MoveYCoord() {
    affine_.Move(data_, value_, Y);
}

void MoveStrategy::MoveZCoord() {
    affine_.Move(data_, value_, Z);
}

// ====================================== R O T A T E ====================================== //
RotateStrategy::RotateStrategy(Data &data, Affine &affine) : data_(data), affine_(affine) {}

void RotateStrategy::Transform(const Action &act, const double &value) {
    value_ = value;
    if (act == RotX)
        RotateXCoord();
    else if (act == RotY)
        RotateYCoord();
    else if (act == RotZ)
        RotateZCoord();
}

void RotateStrategy::RotateXCoord() {
    affine_.Rotate(data_, value_, X);
}

void RotateStrategy::RotateYCoord() {
    affine_.Rotate(data_, value_, Y);
}

void RotateStrategy::RotateZCoord() {
    affine_.Rotate(data_, value_, Z);
}
}
