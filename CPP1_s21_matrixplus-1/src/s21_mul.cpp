#include "s21_matrix_oop.h"

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw runtime_error("Нельзя умножать несогласованные матрицы\n");
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k)
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }
  this->SwapMatrix(tmp);
}