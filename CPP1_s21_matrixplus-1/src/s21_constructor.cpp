#include "s21_matrix_oop.h"

// : для того, чтобы вызвать конструктор для каких-то полей перед выполнением
// самой функции
S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1)
    throw runtime_error(
        "Нельзя создать матрицу с таким количеством столбцов и строчек\n");
  rows_ = rows;
  cols_ = cols;
  // try - сейчас начнется блок, в котором может произойти исключение,
  // отлавливаем исключение catch для обработки исключения
  try {
    matrix_ = new double *[rows_]();
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]();
    }
  } catch (bad_alloc &) {
    rows_ = 0;
    cols_ = 0;
    cout << "Неполучилось выделить память\n";
  }
}

// int main() {
//     S21Matrix a(2, 2);
//     return 0;
// }
