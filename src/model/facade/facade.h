#ifndef CPP_QT_3DVIEWER_MODEL_FACADE_FACADE_H_
#define CPP_QT_3DVIEWER_MODEL_FACADE_FACADE_H_

#include <memory>

#include "../affine/affine.h"
#include "../parser/parser.h"
#include "../strategy/strategy.h"
#include "../struct.h"

namespace s21 {
class Facade {
 public:
  Facade(Facade&& other) = delete;
  Facade(const Facade& other) = delete;
  Facade& operator=(const Facade& other) = delete;

  static Facade& GetInstance(Data& data);

  void Parse(const std::string& path) const;
  void Move(const double& value, const Action& act) const noexcept;
  void Scale(const double& value, const Action& act) const noexcept;
  void Rotate(const double& value, const Action& act) const noexcept;

 private:
  Facade(Data& data);
  ~Facade();

  static Facade* instance_;

  std::unique_ptr<Parser> parser_;
  std::unique_ptr<Affine> affine_;
  std::unique_ptr<Strategy> move_;
  std::unique_ptr<Strategy> scale_;
  std::unique_ptr<Strategy> rotate_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_MODEL_FACADE_FACADE_H_
