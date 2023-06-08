#include <iostream>
#include <stdlib.h>
#include <vector>
#include "matrix.h"
using namespace std;


Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    matrix = new double* [rows];
    for (int row = 0; row < rows; row++) 
    {
        matrix[row] = new double[cols];
        for(int col = 0; col < cols; col++)
        {
            matrix[row][col] = -2.0;
        }
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    matrix = new double* [rows];
    for (int row = 0; row < rows; row++) {
        matrix[row] = new double[cols];
        std::copy(other.matrix[row], other.matrix[row] + cols, matrix[row]);
    }
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        // Free old memory
        for (int row = 0; row < rows; row++) {
            delete[] matrix[row];
        }
        delete[] matrix;

        // Copy sizes
        rows = other.rows;
        cols = other.cols;

        // Allocate and copy new memory
        matrix = new double* [rows];
        for (int row = 0; row < rows; row++) {
            matrix[row] = new double[cols];
            std::copy(other.matrix[row], other.matrix[row] + cols, matrix[row]);
        }
    }

    return *this;
}



Matrix::~Matrix()
{
    // iterate through the rows of the original matrix
    for (int row = 0; row < rows; row++)
    {
        delete matrix[row];
    }
    delete [] matrix;
}


void Matrix::setElement(int row, int col, double value)
{
    if(row >= 0 && row < rows && col >= 0 && col < cols) 
    {
        matrix[row][col] = value;
    }
    else 
    {
        throw std::out_of_range("Row or column value is out of range.");
    }
}

vector<double> Matrix::getRow(int rowIndex) const {
    if (rowIndex >= 0 && rowIndex < this->rows) {
        return std::vector<double>(this->matrix[rowIndex], this->matrix[rowIndex] + this->cols);
    } else {
        // Handle error, either throw an exception or return an empty vector
        throw std::out_of_range("Row index is out of range.");
    }
}
