#ifndef CPP_QT_3DVIEWER_CONTROLLER_CONTROLLER_H_
#define CPP_QT_3DVIEWER_CONTROLLER_CONTROLLER_H_

#include "../model/facade/facade.h"
#include "../model/struct.h"

namespace s21 {
class Controller {
 public:
  Controller(Data &data);
  ~Controller() = default;

  void Parse(const std::string &path) const;
  void Move(const double &value, const Action &act) const noexcept;
  void Scale(const double &value, const Action &act) const noexcept;
  void Rotate(const double &value, const Action &act) const noexcept;

 private:
  Facade &facade_;
};
}  // namespace s21

#endif  // CPP_QT_3DVIEWER_CONTROLLER_CONTROLLER_H_
