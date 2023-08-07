#ifndef SRC_MODEL_FACADE_FACADE_H_
#define SRC_MODEL_FACADE_FACADE_H_

#include "../struct.h"
#include "../parser/parser.h"
#include "../affine/affine.h"

namespace s21 {
    class Facade {
        public:
            Facade() {}
            ~Facade() {}

            const Data& get_data() const noexcept;

            void Parse(const std::string &path) noexcept;
            void Scale(Data &data, const double &value, const bool &div) const noexcept;
            void Move(Data &data, const double &value, const int &coord) const noexcept;
            void Rotate(Data &data, const double &value, const int &coord) const noexcept;

        private:
            Parser parser_;
            Affine affine_;
    };
}

#endif // SRC_MODEL_FACADE_FACADE_H_
