#include <cstdlib>
#include <iostream>
#include "matrix.hpp"

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = (int **)calloc(r, sizeof(int*));
  
  if (_data)
    for(std::size_t i = 0; i < r; i++) 
        _data[i] = (int *)calloc(c, sizeof(int));
}

// Matrix::Matrix(Matrix& m){
//   _rows = m._rows;
//   _cols = m._cols;

//   _data = (int **)calloc(_rows, sizeof(int*));
  
//   if(_data){
//     for(std::size_t i = 0; i < _rows; i++) 
//         _data[i] = (int *)calloc(_cols, sizeof(int));
    
//     for(std::size_t i = 0; i < _rows; i++)
//       for(std::size_t j = 0; j < _cols; j++)
//         _data[i][j] = m._data[i][j];
//   }
// }

Matrix::~Matrix(){
  for (std::size_t i = 0; i < _rows; i++)
    free(_data[i]);
  free(_data);
}

// std::size_t Matrix::get_rows() { return _rows; }
// std::size_t Matrix::get_cols() { return _cols; }

// void Matrix::set(std::size_t i, std::size_t j, int val) {
//   _data[i][j] = val;
// }

// int Matrix::get(std::size_t i, std::size_t j) {
//   return _data[i][j];
// }

// void Matrix::print(FILE* f) {
//   for(std::size_t i = 0; i < _rows; i++){
//       std::cout << _data[i][0];
      
//       for(std::size_t j = 1; j < _cols; j++)
//         std::cout << " " << _data[i][j] ;
      
//       std::cout << std::endl;
//   }
// }

// bool Matrix::operator==(Matrix& m) {
//   bool is_equal = 1;

//   for(std::size_t i = 0; i < _rows; i++)
//     for(std::size_t j = 0; j < _cols; j++)
//       is_equal &= (m._data[i][j] == _data[i][j]);

//   return is_equal;
// }

// bool Matrix::operator!=(Matrix& m) {
//   return !(m==*this);
// }

// Matrix Matrix::operator=(Matrix& m){
//   for (std::size_t i = 0; i < _rows; i++)
//     free(_data[i]);
//   free(_data);
  
//   _rows = m._rows;
//   _cols = m._cols;

//   _data = (int **)calloc(_rows, sizeof(int*));
  
//   if(_data){
//     for(std::size_t i = 0; i < _rows; i++) 
//         _data[i] = (int *)calloc(_cols, sizeof(int));
    
//     for(std::size_t i = 0; i < _rows; i++)
//       for(std::size_t j = 0; j < _cols; j++)
//         _data[i][j] = m._data[i][j];
//   }
//   return *this;
// }

// Matrix& Matrix::operator+=(Matrix& m) {
//   for(std::size_t i = 0; i < _rows; i++)
//     for(std::size_t j = 0; j < _cols; j++)
//       _data[i][j] += m._data[i][j];
//   return *this;
// }

// Matrix& Matrix::operator-=(Matrix& m) {
//   for(std::size_t i = 0; i < _rows; i++)
//     for(std::size_t j = 0; j < _cols; j++)
//       _data[i][j] -= m._data[i][j];
//   return *this;
// }

// Matrix& Matrix::operator*=(Matrix& m) {
//   Matrix mult(_rows, m._cols);

//   for(std::size_t i = 0; i < _rows; i++)
//     for(std::size_t j = 0; j < m._cols; j++)
//       for(std::size_t k = 0; k < _cols; k++)
//         mult._data[i][j] += _data[i][k]*m._data[k][j];    

//   _cols = m._cols;
  
//   *this = mult;
  
//   return *this;
// }

// Matrix Matrix::operator+(Matrix& m) {
//   Matrix tmp(_rows, _cols);
//   tmp += m;
//   tmp += *this;
//   return tmp;
// }

// Matrix Matrix::operator-(Matrix& m) {
//   Matrix tmp(_rows, _cols);
//   tmp -= m;
//   tmp += *this;
//   return tmp;
// }

// Matrix Matrix::operator*(Matrix& m) {
//   Matrix tmp(_rows, _rows);

//   for(std::size_t i = 0; i < tmp._rows; i++)
//     tmp._data[i][i] = 1;

//   tmp *= *this;
//   tmp *= m;

//   return tmp;
// }
