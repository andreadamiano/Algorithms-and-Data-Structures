#include <iostream>

int factorial (int num)
{
    if (num ==0) return 1; //base case to stop the recursion 
    else return num * factorial(num -1); //recursive case to break the problme in smaller subproblems 
}


int main ()
{
    std::cout << factorial(6); 
}