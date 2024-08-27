#include "../s21_matrix_oop.h"

void S21Matrix::ShowMatrix() const {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      cout << matrix_[i][j] << " ";
    }
    cout << "\n";
  }
}