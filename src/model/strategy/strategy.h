#ifndef SRC_MODEL_STRATEGY_STRATEGY_H_
#define SRC_MODEL_STRATEGY_STRATEGY_H_

#include "../struct.h"
#include "../affine/affine.h"

namespace s21 {
class Strategy {
    public:
        virtual ~Strategy() = default;
        virtual void Transform(const Action &act, const double &value) = 0;
};

class ScaleStrategy : public Strategy {
    public:
        ScaleStrategy(Data &data, Affine &affine);
        void Transform(const Action &act, const double &value) override;

    private:
        Data &data_;
        Affine &affine_;
        double value_;

        void Scale(const Action &act);
};

class MoveStrategy : public Strategy {
    public:
        MoveStrategy(Data &data, Affine &affine);
        void Transform(const Action &act, const double &value) override;

    private:
        Data &data_;
        Affine &affine_;
        double value_;

        void Move(const Action &act);
};

class RotateStrategy : public Strategy {
    public:
        RotateStrategy(Data &data, Affine &affine);
        void Transform(const Action &act, const double &value) override;

    private:
        Data &data_;
        Affine &affine_;
        double value_;

        void Rotate(const Action &act);
};
} // namespace s21

#endif // SRC_MODEL_STRATEGY_STRATEGY_H_
