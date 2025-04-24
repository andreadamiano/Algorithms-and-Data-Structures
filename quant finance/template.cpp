#include <iostream>

template <typename T = double>
class Matrix
{
    private: 
        T num; 
    
    public:
        Matrix(const double& _num) : num(_num) {}
}; 

int main () 
{
    Matrix m (10); 
}