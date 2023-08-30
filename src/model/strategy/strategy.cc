#include "strategy.h"

namespace s21 {
// ================================ S C A L E ================================
ScaleStrategy::ScaleStrategy(std::unique_ptr<Affine> &affine)
    : affine_(affine) {}

void ScaleStrategy::Transform(const double &value, const Action &act) {
  if (act == kScaleP)
    affine_->Scale(value, false);
  else if (act == kScaleM)
    affine_->Scale(value, true);
}

// ================================= M O V E =================================
MoveStrategy::MoveStrategy(std::unique_ptr<Affine> &affine)
    : affine_(affine) {}

void MoveStrategy::Transform(const double &value, const Action &act) {
  if (act == kMoveX)
    affine_->Move(value, kX);
  else if (act == kMoveY)
    affine_->Move(value, kY);
  else if (act == kMoveZ)
    affine_->Move(value, kZ);
}

// =============================== R O T A T E ===============================
RotateStrategy::RotateStrategy(std::unique_ptr<Affine> &affine)
    : affine_(affine) {}

void RotateStrategy::Transform(const double &value, const Action &act) {
  if (act == kRotX)
    affine_->Rotate(value, kX);
  else if (act == kRotY)
    affine_->Rotate(value, kY);
  else if (act == kRotZ)
    affine_->Rotate(value, kZ);
}
}  // namespace s21
