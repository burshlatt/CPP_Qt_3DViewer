#ifndef SRC_MODEL_FACADE_FACADE_H_
#define SRC_MODEL_FACADE_FACADE_H_

#include <memory>

#include "../struct.h"
#include "../affine/affine.h"
#include "../parser/parser.h"
#include "../strategy/strategy.h"

namespace s21 {
class Facade {
 public:
  Facade(Facade&& other) = delete;
  Facade(const Facade& other) = delete;
  Facade& operator=(const Facade& other) = delete;

  static Facade& GetInstance(Data& data) noexcept;

  void Parse(const std::string& path) const noexcept;
  void Move(const double &value, const Action& act) const noexcept;
  void Scale(const double &value, const Action& act) const noexcept;
  void Rotate(const double &value, const Action& act) const noexcept;

 private:
  Facade(Data& data);
  ~Facade();

  static Facade* instance_;

  Affine affine_;
  std::unique_ptr<Parser> parser_;
  std::unique_ptr<MoveStrategy> move_;
  std::unique_ptr<ScaleStrategy> scale_;
  std::unique_ptr<RotateStrategy> rotate_;
};
}  // namespace s21

#endif  // SRC_MODEL_FACADE_FACADE_H_
