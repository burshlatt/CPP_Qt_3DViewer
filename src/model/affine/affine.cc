#include "affine.h"

namespace s21 {
void Affine::Move(Data &data, const double &value, const Coord &coord) const noexcept {
  for (int i = 0; i < data.v_count_; i++)
    data.vertexes_[i * 3 + coord] += value;
}

void Affine::Rotate(Data &data, const double &value, const Coord &coord) const noexcept {
  if (coord == X) {
    for (int i = 0; i < data.v_count_; ++i) {
      double *vertex_ = &data.vertexes_[i * 3];
      double y_ = vertex_[1];
      double z_ = vertex_[2];
      vertex_[1] = cos_ * y_ - (sin_ * value) * z_;
      vertex_[2] = cos_ * z_ + (sin_ * value) * y_;
    }
  } else if (coord == Y) {
    for (int i = 0; i < data.v_count_; ++i) {
      double *vertex_ = &data.vertexes_[i * 3];
      double x_ = vertex_[0];
      double z_ = vertex_[2];
      vertex_[0] = cos_ * x_ + (sin_ * value) * z_;
      vertex_[2] = cos_ * z_ - (sin_ * value) * x_;
    }
  } else if (coord == Z) {
    for (int i = 0; i < data.v_count_; ++i) {
      double *vertex_ = &data.vertexes_[i * 3];
      double x_ = vertex_[0];
      double y_ = vertex_[1];
      vertex_[0] = cos_ * x_ - (sin_ * value) * y_;
      vertex_[1] = cos_ * y_ + (sin_ * value) * x_;
    }
  }
}

void Affine::Scale(Data &data, const double &value, const bool &is_div) const noexcept {
  double scale_factor_ = is_div ? 1.0 / value : value;
  for (double &vertex_ : data.vertexes_) vertex_ *= scale_factor_;
}
}  // namespace s21
