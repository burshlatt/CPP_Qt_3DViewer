#include "strategy.h"

namespace s21 {
// ================================ S C A L E ================================
ScaleStrategy::ScaleStrategy(Data &data, Affine &affine)
    : data_(data), affine_(affine) {}

void ScaleStrategy::Transform(const double &value, const Action &act) {
  if (act == ScaleP)
    affine_.Scale(data_, value, false);
  else if (act == ScaleM)
    affine_.Scale(data_, value, true);
}

// ================================= M O V E =================================
MoveStrategy::MoveStrategy(Data &data, Affine &affine)
    : data_(data), affine_(affine) {}

void MoveStrategy::Transform(const double &value, const Action &act) {
  if (act == MoveX)
    affine_.Move(data_, value, X);
  else if (act == MoveY)
    affine_.Move(data_, value, Y);
  else if (act == MoveZ)
    affine_.Move(data_, value, Z);
}

// =============================== R O T A T E ===============================
RotateStrategy::RotateStrategy(Data &data, Affine &affine)
    : data_(data), affine_(affine) {}

void RotateStrategy::Transform(const double &value, const Action &act) {
  if (act == RotX)
    affine_.Rotate(data_, value, X);
  else if (act == RotY)
    affine_.Rotate(data_, value, Y);
  else if (act == RotZ)
    affine_.Rotate(data_, value, Z);
}
}  // namespace s21
