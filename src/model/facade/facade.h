#ifndef SRC_MODEL_FACADE_FACADE_H_
#define SRC_MODEL_FACADE_FACADE_H_

#include "../struct.h"
#include "../parser/parser.h"
#include "../affine/affine.h"
#include "../strategy/strategy.h"

namespace s21 {
    class Facade {
        public:
            Facade(Data &data);
            ~Facade();

            void Parse(const std::string &path) noexcept;
            void Scale(const double &value, const bool &div) const noexcept;
            void Move(const double &value, const Action &act) const noexcept;
            void Rotate(const double &value, const Action &act) const noexcept;

        private:
            Affine affine_;
            Parser *parser_;
            MoveStrategy *move_;
            ScaleStrategy *scale_;
            RotateStrategy *rotate_;
    };
}

#endif // SRC_MODEL_FACADE_FACADE_H_
