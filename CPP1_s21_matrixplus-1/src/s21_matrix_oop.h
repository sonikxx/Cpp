#if !defined(S21_MATRIX_OOP)
#define S21_MATRIX_OOP

#include <cmath>
#include <iostream>

using namespace std;

#define EPS 1e-6

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  void SwapMatrix(S21Matrix &other);
  S21Matrix Minor(int i, int j) const;
  double CalcDeterminant() const;
  void ShowMatrix() const;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);  // конструктор переноса
  ~S21Matrix();

  int GetRows() const;  // const - метод не меняет состояние элемента класса
  int GetCols() const;

  void SetRows(int rows);
  void SetCols(int cols);

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  S21Matrix operator=(const S21Matrix &other);
  void operator+=(const S21Matrix &other);
  void operator-=(const S21Matrix &other);
  void operator*=(const S21Matrix &other);
  void operator*=(const double num);
  double &operator()(int i, int j);
};

#endif  // S21_MATRIX_OOP