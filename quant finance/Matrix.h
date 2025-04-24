#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T = double>
class Matrix
{
    private:
    std::vector<std::vector<T>> matrix; //vector of vectors to store the values of the matrix

    public: 
        Matrix (); 
        Matrix(const int& rows, const int& cols, const T& val); //costructor specifying the rows , columns and a default value 
        Matrix(const Matrix<T>& other); //copy constructor 
        Matrix<T>& operator=(const Matrix<T>& other); //assignment operator overloading    
        virtual ~Matrix(); //destructor 

        const std::vector<std::vector<T>>& getMatrix() const; 
        T& value(const int& row, const int& col); 

        

}; 

#endif