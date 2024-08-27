#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}