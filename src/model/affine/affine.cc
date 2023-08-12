#include "affine.h"

namespace s21 {
void Affine::Move(Data &data, const double &value, const int &coord) const noexcept {
  for (int i = 0; i < data.v_count_; i++)
    data.vertexes_[i * 3 + coord] += value;
}

void Affine::Rotate(Data &data, const double &value, const int &coord) const noexcept {
  double cos_ = std::cos(value);
  double sin_ = std::sin(value);
  for (int i = 0; i < data.v_count_; ++i) {
    double *vertex = &data.vertexes_[i * 3];
    double x_ = vertex[0];
    double y_ = vertex[1];
    double z_ = vertex[2];
    if (coord == 0) {
      vertex[1] = cos_ * y_ - sin_ * z_;
      vertex[2] = sin_ * y_ + cos_ * z_;
    } else if (coord == 1) {
      vertex[0] = sin_ * z_ + cos_ * x_;
      vertex[2] = cos_ * z_ - sin_ * x_;
    } else if (coord == 2) {
      vertex[0] = cos_ * x_ - sin_ * y_;
      vertex[1] = sin_ * x_ + cos_ * y_;
    }
  }
}

void Affine::Scale(Data &data, const double &value, const bool &div) const noexcept {
  double scale_factor = div ? 1.0 / value : value;
  for (double &vertex : data.vertexes_) vertex *= scale_factor;
}
}  // namespace s21
