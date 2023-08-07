#include "facade.h"

namespace s21 {
const Data& Facade::get_data() const noexcept { return parser_.get_data(); }

void Facade::Parse(const std::string &path) noexcept {
    parser_.Parse(path);
}

void Facade::Scale(Data &data, const double &value, const bool &div) const noexcept {
    affine_.Scale(data, value, div);
}

void Facade::Move(Data &data, const double &value, const int &coord) const noexcept {
    affine_.Move(data, value, coord);
}

void Facade::Rotate(Data &data, const double &value, const int &coord) const noexcept {
    affine_.Rotate(data, value, coord);
}
}