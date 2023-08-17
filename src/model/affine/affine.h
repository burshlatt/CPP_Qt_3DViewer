#ifndef SRC_MODEL_AFFINE_AFFINE_H_
#define SRC_MODEL_AFFINE_AFFINE_H_

#include <cmath>

#include "../struct.h"

namespace s21 {
class Affine {
 public:
  Affine() = default;
  ~Affine() = default;

  void Move(Data &data, const double &value, const Coord &coord) const noexcept;
  void Scale(Data &data, const double &value, const bool &is_div) const noexcept;
  void Rotate(Data &data, const double &value, const Coord &coord) const noexcept;

 private:
  const double cos_ = std::cos(0.1);
  const double sin_ = std::sin(0.1);
};
}  // namespace s21

#endif  // SRC_MODEL_AFFINE_AFFINE_H_
