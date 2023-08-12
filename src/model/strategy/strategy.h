#ifndef SRC_MODEL_STRATEGY_STRATEGY_H_
#define SRC_MODEL_STRATEGY_STRATEGY_H_

#include "../affine/affine.h"
#include "../struct.h"

namespace s21 {
// ============================== V I R T U A L ==============================
class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual void Transform(const Action &act, const double &value) = 0;
};

// ================================ S C A L E ================================
class ScaleStrategy : public Strategy {
 public:
  ScaleStrategy(Data &data, Affine &affine);
  void Transform(const Action &act, const double &value) override;

 private:
  Data &data_;
  Affine &affine_;
  double value_;

  void Scale(const Action &act) const noexcept;
};

// ================================= M O V E =================================
class MoveStrategy : public Strategy {
 public:
  MoveStrategy(Data &data, Affine &affine);
  void Transform(const Action &act, const double &value) override;

 private:
  Data &data_;
  Affine &affine_;
  double value_;

  void Move(const Action &act) const noexcept;
};

// =============================== R O T A T E ===============================
class RotateStrategy : public Strategy {
 public:
  RotateStrategy(Data &data, Affine &affine);
  void Transform(const Action &act, const double &value) override;

 private:
  Data &data_;
  Affine &affine_;
  double value_;

  void Rotate(const Action &act) const noexcept;
};
}  // namespace s21

#endif  // SRC_MODEL_STRATEGY_STRATEGY_H_
