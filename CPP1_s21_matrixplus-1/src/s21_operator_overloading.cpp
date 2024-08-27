#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {  // b = b
    S21Matrix tmp(other);
    this->SwapMatrix(tmp);
  }
  return *this;
}

void S21Matrix::operator+=(const S21Matrix &other) { this->SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix &other) { this->SubMatrix(other); }

void S21Matrix::operator*=(const S21Matrix &other) { this->MulMatrix(other); }

void S21Matrix::operator*=(const double num) { this->MulNumber(num); }

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw runtime_error("Индекс за пределами матрицы\n");
  return matrix_[i][j];
}