#include "../s21_matrix_oop.h"

void S21Matrix::SwapMatrix(S21Matrix &other) {
  swap(rows_, other.rows_);
  swap(cols_, other.cols_);
  swap(matrix_, other.matrix_);
}