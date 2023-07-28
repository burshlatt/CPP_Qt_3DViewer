#ifndef SRC_MODEL_AFFINE_H_
#define SRC_MODEL_AFFINE_H_

#include "parser.h"

namespace s21 {
    class Affine {
        public:
            Affine() {}
            ~Affine() {}

            void MoveX(Data &data, const double &value);
            void MoveY(Data &data, const double &value);
            void MoveZ(Data &data, const double &value);
            void RotateOX(Data &data, const double &value);
            void RotateOY(Data &data, const double &value);
            void RotateOZ(Data &data, const double &value);

            // void scale(matrix_t *A, const double &X, const double &Y, const double &Z);
            // void scale_div(matrix_t *A, const double &X, const double &Y, const double &Z);
    };
}

#endif // SRC_MODEL_AFFINE_H_
