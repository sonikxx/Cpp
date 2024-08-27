#include "s21_matrix_oop.h"

void S21Matrix::SetRows(int rows) {
  if (rows < 1) throw runtime_error("Число строк должно быть натуральным\n");
  S21Matrix tmp_matrix(rows, cols_);
  for (int i = 0; i < min(tmp_matrix.rows_, rows_); ++i) {
    for (int j = 0; j < cols_; ++j) {
      tmp_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  this->SwapMatrix(tmp_matrix);
}

void S21Matrix::SetCols(int cols) {
  if (cols < 1) throw runtime_error("Число столбцов должно быть натуральным\n");
  S21Matrix tmp_matrix(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < min(tmp_matrix.cols_, cols_); ++j) {
      tmp_matrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  this->SwapMatrix(tmp_matrix);
}
