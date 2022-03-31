#include <cstdlib>
#include <iostream>
#include <cstring>

#include "matrix.h"

int** init_matrix(std::size_t r, std::size_t c){
  int** matrix = new int*[r];

  for(std::size_t i = 0; i < r; i++) 
      matrix[i] = new int[c];

  for(std::size_t i = 0; i < r; i++) 
    memset(matrix[i], 0, sizeof(int) * c);

  // std:: cout << sizeof(matrix[0]) << std::endl;
  return matrix;
  
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
        memcpy(_data[i], m._data[i], sizeof(int) * _cols);
  else
    exit(1);
  
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
  bool is_equal = true;

  is_equal &= (_rows == m._rows) && (_cols == m._cols);

  if(is_equal)
    for(std::size_t i = 0; i < _rows; i++)
      for(std::size_t j = 0; j < _cols; j++)
        is_equal &= (m._data[i][j] == _data[i][j]);

  return is_equal;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(m==*this);
}

Matrix& Matrix::operator=(const Matrix& m){
  // for (std::size_t i = 0; i < _rows; i++)
  //   delete[] _data[i];
  // delete[] _data;
  
  // _rows = m._rows;
  // _cols = m._cols;
  // _data = init_matrix(_rows, _cols);

  // if(_data)
  //   for(std::size_t i = 0; i < _rows; i++)
  //     for(std::size_t j = 0; j < _cols; j++)
  //       _data[i][j] = m._data[i][j];
  Matrix tmp(m);
  std::swap(tmp, *this);
  tmp.~Matrix();  

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
  Matrix tmp(*this);
  tmp *= m;
  return tmp;
}
