#include <cstdlib>
#include <iostream>
#include <cstring>

#include "matrix.hpp"

int** init_matrix(std::size_t r, std::size_t c){
    int** matrix = new int*[r];

    if(!matrix)
        throw MatrixException("Unable to allocate memory.");

    for(std::size_t i = 0; i < r; i++){ 
        matrix[i] = new int[c];
        if (!matrix[i])
            throw MatrixException("Unable to allocate memory.");
    }

    for(std::size_t i = 0; i < r; i++) 
        memset(matrix[i], 0, sizeof(int) * c);

    return matrix;
  
}

Matrix::Matrix(){
    _rows = 0;
    _cols = 0;
    _data = init_matrix(_rows, _cols);
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

    for(std::size_t i = 0; i < _rows; i++)
        memcpy(_data[i], m._data[i], sizeof(int) * _cols);
}

Matrix::~Matrix(){
    for (std::size_t i = 0; i < _rows; i++)
        delete[] _data[i];
    delete[] _data;
}

std::size_t Matrix::get_rows() const { return _rows; }
std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, const int& val) { _data[i][j] = val; }

int Matrix::get(std::size_t i, std::size_t j) const { 
    if(i < 0 || j < 0 || i >= _rows || j >= _cols)
        throw MatrixException("ACCESS: bad index.");

    return _data[i][j]; 
}

void Matrix::print() const {
    // FILE* f = stdout;
    if(_rows != 0 || _cols != 0)    
        for(std::size_t i = 0; i < _rows; i++){
            // fprintf(f, "%d", _data[i][0]);
            std::cout << _data[i][0];
            
            for(std::size_t j = 1; j < _cols; j++)
                // fprintf(f, " %d", _data[i][j]) ;
                std::cout << " " << _data[i][j];
            
            // fprintf(f, "\n");
            std::cout << std::endl;
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
    this->~Matrix();

    _rows = m._rows;
    _cols = m._cols;
    _data = init_matrix(_rows, _cols);

    for(std::size_t i = 0; i < _rows; i++)
        memcpy(_data[i], m._data[i], sizeof(int) * _cols);

    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    if(_rows != m._rows || _cols != m._cols)
        throw MatrixException("ADD: dimensions do not match.");
    
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

Matrix &Matrix::operator*=(const Matrix &matrix) {
    *this = *this * matrix;
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

Matrix Matrix::operator*(const Matrix &matrix) const {
    if (_cols != matrix._rows)
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");

    Matrix matrix_result(_rows, matrix._cols);

    for (std::size_t i = 0; i < matrix_result._rows; i++)
        for (std::size_t j = 0; j < matrix_result._cols; j++)
            for (std::size_t k = 0; k < _cols; k++)
                matrix_result._data[i][j] += _data[i][k] * matrix._data[k][j];

    return matrix_result;
}

Matrix read_matrix_from_file(std::string filename){
    std::ifstream fs(filename);

    if(!fs)
        throw MatrixException("LOAD: unable to open file.");
        
    int rows, cols;
    
    if(!(fs >> rows >> cols))
        throw MatrixException("LOAD: invalid file format.");

    int data[rows][cols];
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++){
            if(!(fs >> data[i][j]))
                throw MatrixException("LOAD: invalid file format.");
        }
    
    Matrix m = Matrix(rows, cols);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            m.set(i, j, data[i][j]);

    fs.close();
    // m.print();

    return m;
}

int Registers::get_reg(const std::string strreg) const{
    return atoi(strreg.c_str() + sizeof(char));
}

void Registers::load(const Matrix& m, int reg){
    registers[reg] = m;
}

void Registers::print(int reg) const{
    registers[reg].print();
}

void Registers::add(int reg1, int reg2){
    registers[reg1] += registers[reg2];
}

void Registers::mul(int reg1, int reg2){
    registers[reg1] *= registers[reg2];
}

void Registers::elem(int reg, int row, int col) const{
    std::cout << registers[reg].get(row,col) << std::endl;
}
