#include <iostream>
#include <vector>

int main ()
{
    // int matrix[10][10]; //the first 10 represents the rows and the second the columns
    // matrix[0][0] = 7; 

    // std::cout << matrix[0][0] << std::endl; 


    //dynamic allocation of a matrix
    // int rows (10); 
    // int columns (10); 

    // int** matrix = new int* [rows]; //a amtrix is an array of array , so an array of row pointer 
    // for (int i=0; i<rows; i++)
    // {
    //     matrix[i] = new int [columns]; //allocate dynamically the ith row 
    // }

    // //access an element of a matrix dynamically allocated 
    // matrix[0][0] = 1; 
    // std::cout << matrix[0][0] << std::endl; 


    // //deallocate memory 
    // for (int i=0; i< rows; i++)
    // {
    //     delete[] matrix[i]; 
    // }

    // delete[] matrix; 


    //stl implementation of a dynamic vector 
    int rows (10); 
    int columns (10); 
    std::vector<std::vector<int> > matrix (rows, std::vector<int> (columns));
}
