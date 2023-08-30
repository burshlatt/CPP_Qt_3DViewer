#ifndef CPP_QT_3DVIEWER_MODEL_STRATEGY_STRATEGY_H_
#define CPP_QT_3DVIEWER_MODEL_STRATEGY_STRATEGY_H_

#include "../affine/affine.h"
#include "../struct.h"

namespace s21 {
// ============================== V I R T U A L ==============================
class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual void Transform(const double &value, const Action &act) = 0;
};

// ================================ S C A L E ================================
class ScaleStrategy : public Strategy {
 public:
  ScaleStrategy(std::unique_ptr<Affine> &affine);
  void Transform(const double &value, const Action &act) override;

 private:
  std::unique_ptr<Affine> &affine_;
};

// ================================= M O V E =================================
class MoveStrategy : public Strategy {
 public:
  MoveStrategy(std::unique_ptr<Affine> &affine);
  void Transform(const double &value, const Action &act) override;

 private:
  std::unique_ptr<Affine> &affine_;
};

// =============================== R O T A T E ===============================
class RotateStrategy : public Strategy {
 public:
  RotateStrategy(std::unique_ptr<Affine> &affine);
  void Transform(const double &value, const Action &act) override;

 private:
  std::unique_ptr<Affine> &affine_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_MODEL_STRATEGY_STRATEGY_H_
