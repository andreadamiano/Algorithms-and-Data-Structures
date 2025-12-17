#include <iostream>
#include <cstdlib> 

int main()
{
    int x, y; 
    std::cout << "please insert 2 numbers: ";
    std::cin >> x >> y; 
    
    int sum = x+y; 
    std::cout << "their sum is: " << sum ; 
    return 0; 

}