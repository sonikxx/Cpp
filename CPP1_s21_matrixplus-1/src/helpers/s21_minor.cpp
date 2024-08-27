#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::Minor(int i, int j) const {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int ki = 0;
  for (int new_i = 0; new_i < result.rows_; ++new_i) {
    int kj = 0;
    if (new_i == i) ki = 1;
    for (int new_j = 0; new_j < result.cols_; ++new_j) {
      if (new_j == j) kj = 1;
      if (new_i + ki < rows_ && new_j + kj < cols_)
        result.matrix_[new_i][new_j] = matrix_[new_i + ki][new_j + kj];
    }
  }
  return result;
}