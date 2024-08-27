#include "s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() const {
  S21Matrix result(*this);
  if (rows_ != cols_)
    throw runtime_error(
        "Матрицу алгебраических дополнений можно найти только для квадратной "
        "матрицы\n");
  if (rows_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        S21Matrix new_matrix = this->Minor(i, j);
        double minor_det = new_matrix.Determinant();
        result.matrix_[i][j] = pow(-1, i + j) * minor_det;
      }
    }
  }
  return result;
}