#ifndef LAB_07_MATRIX_HPP
#define LAB_07_MATRIX_HPP

#include <cstdio>
#include <cstddef>
#include <array>
#include <fstream>
#include <exception>

int** init_matrix(std::size_t r, std::size_t c);

class Matrix {
    public:
    Matrix();
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix& m);

    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t i, std::size_t j, const int& val);
    int get(std::size_t i, std::size_t j) const;
    void print() const;

    ~Matrix();
    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    
    bool operator==(const Matrix& m) const;
    bool operator!=(const Matrix& m) const;
    
    
    private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};

Matrix read_matrix_from_file(std::string filename);

class Registers{
    public:
    void load(const Matrix& m, int reg);
    void print(int reg) const;
    void add(int reg1, int reg2);
    void mul(int reg1, int reg2);
    void elem(int reg, int row, int col) const;

    int get_reg(const std::string strreg) const;

    private:
    std::array<Matrix, 10> registers;
};

class MatrixException : public std::exception {
    
    public:
        explicit MatrixException(const char* message)
                : what_message(message) {}

        const char* what() const noexcept override { return what_message.c_str(); }
    
    private:
        std::string what_message;
};

#endif
