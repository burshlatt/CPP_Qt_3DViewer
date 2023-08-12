#ifndef SRC_MODEL_AFFINE_AFFINE_H_
#define SRC_MODEL_AFFINE_AFFINE_H_

#include <cmath>

#include "../struct.h"

namespace s21 {
class Affine {
 public:
  Affine() = default;
  ~Affine() = default;

  void Scale(Data &data, const double &value, const bool &div) const noexcept;
  void Move(Data &data, const double &value, const int &coord) const noexcept;
  void Rotate(Data &data, const double &value, const int &coord) const noexcept;
};
}  // namespace s21

#endif  // SRC_MODEL_AFFINE_AFFINE_H_
