#ifndef CPP_QT_3DVIEWER_MODEL_AFFINE_AFFINE_H_
#define CPP_QT_3DVIEWER_MODEL_AFFINE_AFFINE_H_

#include <cmath>

#include "../struct.h"

namespace s21 {
class Affine {
 public:
  Affine(Data &data);
  ~Affine() = default;

  void Move(const double &value, const Coord &coord) const noexcept;
  void Scale(const double &value, const bool &is_div) const noexcept;
  void Rotate(const double &value, const Coord &coord) const noexcept;

 private:
  Data &data_;
  const double cos_value_ = std::cos(1 * (M_PI / 180.0));
  const double sin_value_ = std::sin(1 * (M_PI / 180.0));
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_MODEL_AFFINE_AFFINE_H_
