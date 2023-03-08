#include "s21_matrix_oop.h"

// constructors
S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) throw std::out_of_range("invalid length!");
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

// accessors
int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }

// mutators
void S21Matrix::setRows(int rows) {
  if (rows <= 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  S21Matrix result(rows, cols_);
  for (int i = 0; i < rows_ && i < result.rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = result;
}
void S21Matrix::setCols(int cols) {
  if (cols <= 0)
    throw std::out_of_range("Incorrect input, index is out of range");

  S21Matrix result(rows_, cols);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_ && j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = result;
}

// operations
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("invalid size of matrix!");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range("invalid size of matrix!");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_ || !other.isValid() || !this->isValid())
    throw std::logic_error("invalid size of matrix!");

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::out_of_range("invalid size of matrix!");

  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix complementMatrix = this->GetComplementMatrix(i, j);
      result.matrix_[i][j] = complementMatrix.Determinant();
      if ((i + j) % 2) result.matrix_[i][j] *= -1;
    }
  }
  return result;
}
double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::out_of_range("invalid size of matrix!");

  double result = 0, temp = 0;
  int sign = 1;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix complementMatrix = this->GetComplementMatrix(0, j);
      temp = complementMatrix.Determinant();
      result += sign * matrix_[0][j] * temp;
      sign *= -1;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::invalid_argument("invalid size of matrix!");

  double det = this->Determinant();
  if (fabs(det) < 1e-7) throw std::invalid_argument("invalid matrix!");

  S21Matrix minor = this->CalcComplements();
  S21Matrix result = minor.Transpose();
  result.MulNumber(1.0 / det);
  return result;
}

// operators
S21Matrix S21Matrix::operator+(const S21Matrix &o) {
  S21Matrix result(*this);
  result.SumMatrix(o);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &o) {
  S21Matrix result(*this);
  result.SubMatrix(o);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &o) {
  S21Matrix result(*this);
  result.MulMatrix(o);
  return result;
}
S21Matrix S21Matrix::operator*(const double o) {
  S21Matrix result(*this);
  result.MulNumber(o);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &o) { return this->EqMatrix(o); }

S21Matrix &S21Matrix::operator=(const S21Matrix &o) {
  if (this != &o) {
    deleteMatrix();

    rows_ = o.rows_;
    cols_ = o.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]();
    }

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = o.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &o) {
  this->SumMatrix(o);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &o) {
  this->SubMatrix(o);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &o) {
  this->MulMatrix(o);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double o) {
  this->MulNumber(o);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
    throw std::out_of_range("index is out of range");
  return matrix_[row][col];
}

// helpers
S21Matrix S21Matrix::GetComplementMatrix(int i_row, int j_col) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int set_row = 0, set_col = 0;
  for (int i = 0; i < result.rows_; ++i) {
    if (i == i_row) set_row = 1;
    set_col = 0;
    for (int j = 0; j < result.cols_; ++j) {
      if (j == j_col) set_col = 1;
      result.matrix_[i][j] = matrix_[i + set_row][j + set_col];
    }
  }
  return result;
}

void S21Matrix::FillingMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = i * cols_ + j;
    }
  }
}

void S21Matrix::ZeroingMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

bool S21Matrix::isValid() const {
  if (rows_ < 1 || cols_ < 1 || matrix_ == nullptr) return false;
  return true;
}

void S21Matrix::deleteMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[](matrix_[i]);
    }
    delete[] matrix_;
  }
}

// destructor
S21Matrix::~S21Matrix() { deleteMatrix(); }
