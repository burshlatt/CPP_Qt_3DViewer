#include "affine.h"

namespace s21 {
void Affine::Move(Data &data, const double &value, const int &coord) const noexcept {
  for (int i = 0; i < data.v_count_; i++) {
    data.vertexes_[i * 3 + coord] += value;
  }
}

void Affine::Rotate(Data &data, const double &value, const int &coord) const noexcept {
  double cos_ = cos(value);
  double sin_ = sin(value);
  for (int i = 0; i < data.v_count_; i++) {
    double x_ = data.vertexes_[i * 3];
    double y_ = data.vertexes_[i * 3 + 1];
    double z_ = data.vertexes_[i * 3 + 2];
    if (coord == 0) {
      data.vertexes_[i * 3 + 1] = cos_ * y_ - sin_ * z_;
      data.vertexes_[i * 3 + 2] = sin_ * y_ + cos_ * z_;
    } else if (coord == 1) {
      data.vertexes_[i * 3] = sin_ * z_ + cos_ * x_;
      data.vertexes_[i * 3 + 2] = cos_ * z_ - sin_ * x_;
    } else if (coord == 2) {
      data.vertexes_[i * 3] = cos_ * x_ - sin_ * y_;
      data.vertexes_[i * 3 + 1] = sin_ * x_ + cos_ * y_;
    }
  }
}

void Affine::ScaleMul(Data &data, const double &value) const noexcept {
  for (size_t i = 0; i < data.vertexes_.size(); i += 3) {
    data.vertexes_[i] *= value;
    data.vertexes_[i + 1] *= value;
    data.vertexes_[i + 2] *= value;
  }
}

void Affine::ScaleDiv(Data &data, const double &value) const noexcept {
  for (size_t i = 0; i < data.vertexes_.size(); i += 3) {
    data.vertexes_[i] /= value;
    data.vertexes_[i + 1] /= value;
    data.vertexes_[i + 2] /= value;
  }
}
}
