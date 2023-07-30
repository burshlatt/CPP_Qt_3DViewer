#ifndef SRC_MODEL_AFFINE_H_
#define SRC_MODEL_AFFINE_H_

#include "parser.h"

namespace s21 {
    class Affine {
        public:
            Affine() {}
            ~Affine() {}

            void ScaleMul(Data &data, const double &value) const noexcept;
            void ScaleDiv(Data &data, const double &value) const noexcept;
            void Move(Data &data, const double &value, const int &coord) const noexcept;
            void Rotate(Data &data, const double &value, const int &coord) const noexcept;
    };
}

#endif // SRC_MODEL_AFFINE_H_
