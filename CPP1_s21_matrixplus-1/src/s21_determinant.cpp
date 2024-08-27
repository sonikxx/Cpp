#include "s21_matrix_oop.h"

double S21Matrix::Determinant() const {
  double result = 0;
  if (rows_ != cols_)
    throw runtime_error("Нельзя найти определитель неквадратной матрицы\n");
  if (rows_ == 1) result = matrix_[0][0];
  if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  if (rows_ > 2) result = this->CalcDeterminant();
  return result;
}

double S21Matrix::CalcDeterminant() const {
  double result = 0;
  if (rows_ == 1) return matrix_[0][0];
  for (int i = 0; i < rows_; ++i) {
    S21Matrix new_matrix = this->Minor(0, i);
    result += pow(-1, i) * matrix_[0][i] * new_matrix.CalcDeterminant();
  }
  return result;
}