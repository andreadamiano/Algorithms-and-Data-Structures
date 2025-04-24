#include <iostream>
#include "Matrix.h"

template< typename T>
Matrix<T>::Matrix()
{
    //no need to implement since we rely on the default constructor of the vector 
}

template< typename T>
Matrix<T>::Matrix(const int& rows, const int& cols, const T& val)
{
    for (int i = 0; i<rows; ++i)
    {
        std::vector<T> row_vector(cols, val); 
        matrix.push_back(row_vector); 
    }
}

template< typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
    matrix = other.getMatrix(); 
}

template< typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if (this != &other)
    {
        matrix = other.getMatrix();
    }
    return *this; 
}

template< typename T>
Matrix<T>::~Matrix()
{
    //no need to implement since we rely on the destructor of the vector 
}

template< typename T>
const std::vector<std::vector<T>>& Matrix<T>::getMatrix() const 
{
    return matrix; 
} 

template< typename T>
T& Matrix<T>::value(const int& row, const int& col)
{
    return matrix[row][col]; 
}

int main ()
{
    Matrix matrix(10, 10, 0.0); 

    std::cout << matrix.value(4,4);

}