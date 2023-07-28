#include "affine.h"

namespace s21 {
void Affine::MoveX(Data &data, const double &value) {
  for (int i = 0; i < data.facets_.size(); i += 3)
    data.facets_[i] += value;
}

void Affine::MoveY(Data &data, const double &value) {
  for (int i = 1; i < data.facets_.size(); i += 3)
    data.facets_[i] += value;
}

void Affine::MoveZ(Data &data, const double &value) {
  for (int i = 2; i < data.facets_.size(); i += 3)
    data.facets_[i] += value;
}

void Affine::RotateOX(Data &data, const double &value) {
  for (int i = 2; i < data.facets_.size(); i += 3) {
    double y_ = data.facets_[i - 1];
    double z_ = data.facets_[i];
    data.facets_[i - 1] = cos(value) * y_ - sin(value) * z_;
    data.facets_[i] = sin(value) * y_ + cos(value) * z_;
  }
}

void Affine::RotateOY(Data &data, const double &value) {
  for (int i = 2; i < data.facets_.size(); i += 3) {
    double x_ = data.facets_[i - 2];
    double z_ = data.facets_[i];
    data.facets_[i - 2] = sin(value) * z_ + cos(value) * x_;
    data.facets_[i] = cos(value) * z_ - sin(value) * x_;
  }
}

void Affine::RotateOZ(Data &data, const double &value) {
  for (int i = 1; i < data.facets_.size(); i += 3) {
    double x_ = data.facets_[i - 1];
    double y_ = data.facets_[i];
    data.facets_[i - 1] = cos(value) * x_ - sin(value) * y_;
    data.facets_[i] = sin(value) * x_ + cos(value) * y_;
  }
}

// void Affine::scale(matrix_t *A, double X, double Y, double Z) {
//   for (int i = 0; i < A->rows; i++) {
//     A->matrix[i][0] *= X;
//     A->matrix[i][1] *= Y;
//     A->matrix[i][2] *= Z;
//   }
// }

// void Affine::scale_div(matrix_t *A, double X, double Y, double Z) {
//   for (int i = 0; i < A->rows; i++) {
//     A->matrix[i][0] /= X;
//     A->matrix[i][1] /= Y;
//     A->matrix[i][2] /= Z;
//   }
// }
}
