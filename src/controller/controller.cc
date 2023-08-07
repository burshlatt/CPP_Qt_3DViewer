#include "controller.h"

namespace s21 {
const Data& Controller::get_data() noexcept {
    data_ = facade_.get_data();
    data_.max_coord_ *= 1.5;
    data_.far_ = (data_.max_coord_ + 10) * 10;
    data_.near_ = data_.max_coord_ / (2 * tan(60.0 * M_PI / 180 / 2));
    return data_;
}

void Controller::Parse(const std::string &path) noexcept {
    facade_.Parse(path);
}

void Controller::Scale(Data &data, const double &value, const bool &div) const noexcept {
    facade_.Scale(data, value, div);
}

void Controller::Move(Data &data, const double &value, const int &coord) const noexcept {
    facade_.Move(data, value, coord);
}

void Controller::Rotate(Data &data, const double &value, const int &coord) const noexcept {
    facade_.Rotate(data, value, coord);
}
}