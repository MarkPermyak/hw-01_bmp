#include <cstdlib>
#include <iostream>
#include "matrix.hpp"

int** init_matrix(std::size_t r, std::size_t c){
  int** matrix = new int*[r];

  if (matrix){
    for(std::size_t i = 0; i < r; i++) 
        matrix[i] = new int[c]();

    for(std::size_t i = 0; i < r; i++) 
      for(std::size_t j = 0; j < c; j++) 
        matrix[i][j] = 0;

  return matrix;
  }
  return 0;
}

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = init_matrix(_rows, _cols);
}

Matrix::Matrix(const Matrix& m){
  _rows = m._rows;
  _cols = m._cols;

  _data = init_matrix(_rows, _cols);

  if(_data)  
    for(std::size_t i = 0; i < _rows; i++)
      for(std::size_t j = 0; j < _cols; j++)
        _data[i][j] = m._data[i][j];
  
}

Matrix::~Matrix(){
  for (std::size_t i = 0; i < _rows; i++)
    delete[] _data[i];
  delete[] _data;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for(std::size_t i = 0; i < _rows; i++){
      fprintf(f, "%d", _data[i][0]);
      
      for(std::size_t j = 1; j < _cols; j++)
        fprintf(f, " %d", _data[i][j]) ;
      
      fprintf(f, "\n");
  }
}

bool Matrix::operator==(const Matrix& m) const {
  bool is_equal = 1;

  for(std::size_t i = 0; i < _rows; i++)
    for(std::size_t j = 0; j < _cols; j++)
      is_equal &= (m._data[i][j] == _data[i][j]);

  return is_equal;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(m==*this);
}

Matrix& Matrix::operator=(const Matrix& m){
  this->~Matrix();
  
  _rows = m._rows;
  _cols = m._cols;
  _data = init_matrix(_rows, _cols);

  if(_data)
    for(std::size_t i = 0; i < _rows; i++)
      for(std::size_t j = 0; j < _cols; j++)
        _data[i][j] = m._data[i][j];
  
  return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for(std::size_t i = 0; i < _rows; i++)
    for(std::size_t j = 0; j < _cols; j++)
      _data[i][j] += m._data[i][j];
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  for(std::size_t i = 0; i < _rows; i++)
    for(std::size_t j = 0; j < _cols; j++)
      _data[i][j] -= m._data[i][j];
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  Matrix mult(_rows, m._cols);

  for(std::size_t i = 0; i < _rows; i++)
    for(std::size_t j = 0; j < m._cols; j++)
      for(std::size_t k = 0; k < _cols; k++)
        mult._data[i][j] += _data[i][k]*m._data[k][j];    

  _cols = m._cols;
  
  *this = mult;
  
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix tmp(*this);
  tmp += m;
  return tmp;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix tmp(*this);
  tmp -= m;
  return tmp;
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix tmp(_rows, _rows);

  for(std::size_t i = 0; i < tmp._rows; i++)
    tmp._data[i][i] = 1;

  tmp *= *this;
  tmp *= m;

  return tmp;
}
