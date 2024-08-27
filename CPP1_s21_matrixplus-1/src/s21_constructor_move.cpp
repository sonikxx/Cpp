#include "s21_matrix_oop.h"

// && ссылка на обьект, который умрет, после вызова этой функции, временный
// обьект, r-value ссылка
S21Matrix::S21Matrix(S21Matrix &&other) {
  this->SwapMatrix(other);
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}
