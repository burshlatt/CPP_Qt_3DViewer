#include "affine.h"

namespace s21 {
void Affine::Move(Data &data, const double &value, const Coord &coord) const noexcept {
  for (int i = 0; i < data.v_count_; i++)
    data.vertexes_[i * 3 + coord] += value;
}

void Affine::Rotate(Data &data, const double &value, const Coord &coord) const noexcept {
  double cos_ = std::cos(value);
  double sin_ = std::sin(value);
  if (coord == X) {
    for (int i = 0; i < data.v_count_; ++i) {
      double *vertex_ = &data.vertexes_[i * 3];
      double y_ = vertex_[1];
      double z_ = vertex_[2];
      vertex_[1] = cos_ * y_ - sin_ * z_;
      vertex_[2] = sin_ * y_ + cos_ * z_;
    }
  } else if (coord == Y) {
    for (int i = 0; i < data.v_count_; ++i) {
      double *vertex_ = &data.vertexes_[i * 3];
      double x_ = vertex_[0];
      double z_ = vertex_[2];
      vertex_[0] = sin_ * z_ + cos_ * x_;
      vertex_[2] = cos_ * z_ - sin_ * x_;
    }
  } else if (coord == Z) {
    for (int i = 0; i < data.v_count_; ++i) {
      double *vertex_ = &data.vertexes_[i * 3];
      double x_ = vertex_[0];
      double y_ = vertex_[1];
      vertex_[0] = cos_ * x_ - sin_ * y_;
      vertex_[1] = sin_ * x_ + cos_ * y_;
    }
  }
}

void Affine::Scale(Data &data, const double &value, const bool &div) const noexcept {
  double scale_factor = div ? 1.0 / value : value;
  for (double &vertex_ : data.vertexes_) vertex_ *= scale_factor;
}
}  // namespace s21
