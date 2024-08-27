#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result;
  if (rows_ != cols_)
    throw runtime_error("Нельзя обратить неквадратную матрицу\n");
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    double det = this->CalcDeterminant();
    if (det == 0) throw runtime_error("Определитель матрицы равен 0\n");
    S21Matrix new_1 = this->CalcComplements();
    result = new_1.Transpose();
    result.MulNumber(1.0 / det);
  }
  return result;
}