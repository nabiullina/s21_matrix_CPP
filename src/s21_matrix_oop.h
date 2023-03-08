#ifndef S21_MATRIX_S21MATRIX_H
#define S21_MATRIX_S21MATRIX_H

#include <math.h>

#include <stdexcept>

class S21Matrix {
 public:
  // constructors
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // accessors
  int getRows() const;
  int getCols() const;

  // mutators
  void setRows(int rows);
  void setCols(int cols);

  // operations
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // operators
  S21Matrix& operator=(const S21Matrix& o);
  double& operator()(int row, int col);
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix& operator*=(const double o);
  S21Matrix operator*(const double o);
  S21Matrix& operator*=(const S21Matrix& o);
  bool operator==(const S21Matrix& o);

  // helpers
  void FillingMatrix();
  void ZeroingMatrix();

 private:
  int rows_, cols_;
  double** matrix_;

  // helpers
  void deleteMatrix();
  bool isValid() const;
  S21Matrix GetComplementMatrix(int i, int j);
};

#endif  // S21_MATRIX_S21MATRIX_H
