#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool flag = true;
  if (rows_ != other.rows_ || cols_ != other.cols_)
    flag = false;
  else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) flag = false;
      }
    }
  }
  return flag;
}
