#ifndef MATRIX_H
#define MATRIX_H
#include <vector>  // This includes std::vector

class Matrix
{
public:
    // default constructor 
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    // pointer to a series of pointers called matrix
    double** matrix;

    // Destructor method will deallocate memory
    ~Matrix(); 

    // Set Element of A matrix

    void setElement(int row, int col, double value);

    std::vector<double> getRow(int rowIndex) const;

    //
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    double** getMat() const { return matrix; }

    

private:
    int rows;
    int cols;
};
#endif