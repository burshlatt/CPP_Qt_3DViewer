#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/struct.h"
#include "../model/facade/facade.h"

namespace s21 {
    class Controller {
        public:
            Controller(Data &data);
            ~Controller();

            void Parse(const std::string &path) noexcept;
            void Move(const double &value, const Action &act) const noexcept;
            void Scale(const double &value, const Action &act) const noexcept;
            void Rotate(const double &value, const Action &act) const noexcept;

        private:
            Facade *facade_;
    };
}

#endif // SRC_CONTROLLER_CONTROLLER_H_
