#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/struct.h"
#include "../model/facade/facade.h"

namespace s21 {
    class Controller {
        public:
            Controller() {}
            ~Controller() {}

            const Data& get_data() noexcept;

            void Parse(const std::string &path) noexcept;
            void Scale(Data &data, const double &value, const bool &div) const noexcept;
            void Move(Data &data, const double &value, const int &coord) const noexcept;
            void Rotate(Data &data, const double &value, const int &coord) const noexcept;

        private:
            Data data_;
            Facade facade_;
    };
}

#endif // SRC_CONTROLLER_CONTROLLER_H_
