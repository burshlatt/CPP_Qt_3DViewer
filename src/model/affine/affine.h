#ifndef SRC_MODEL_AFFINE_AFFINE_H_
#define SRC_MODEL_AFFINE_AFFINE_H_

#include <cmath>

#include "../struct.h"

namespace s21 {
    class Affine {
        public:
            Affine() {}
            ~Affine() {}

            void Scale(Data &data, const double &value, const bool &div) const noexcept;
            void Move(Data &data, const double &value, const int &coord) const noexcept;
            void Rotate(Data &data, const double &value, const int &coord) const noexcept;
    };
}

#endif // SRC_MODEL_AFFINE_AFFINE_H_