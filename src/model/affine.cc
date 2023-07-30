#include "affine.h"

namespace s21 {
void Affine::Move(Data &data, const double &value, const int &coord) const noexcept {
  for (int i = 0; i < data.v_count_; i++) {
    data.vertexes_[i * 3 + coord] += value;
  }
}

void Affine::Rotate(Data &data, const double &value, const int &coord) const noexcept {
  for (int i = 0; i < data.v_count_; i++) {
    double x_ = data.vertexes_[i * 3];
    double y_ = data.vertexes_[i * 3 + 1];
    double z_ = data.vertexes_[i * 3 + 2];
    if (coord == 0) {
      data.vertexes_[i * 3 + 1] = cos(value) * y_ - sin(value) * z_;
      data.vertexes_[i * 3 + 2] = sin(value) * y_ + cos(value) * z_;
    } else if (coord == 1) {
      data.vertexes_[i * 3] = sin(value) * z_ + cos(value) * x_;
      data.vertexes_[i * 3 + 2] = cos(value) * z_ - sin(value) * x_;
    } else if (coord == 2) {
      data.vertexes_[i * 3] = cos(value) * x_ - sin(value) * y_;
      data.vertexes_[i * 3 + 1] = sin(value) * x_ + cos(value) * y_;
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
