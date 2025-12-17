#include <iostream>

int main ()
{
    const int num = 10;
    // num = 20; // error: assignment of read-only variable ‘num’
    std::cout << num << std::endl;  

    const int* p = &num; //you cannot modify the variable throuhg the pointer 
    // *p = 20; // error: assignment of read-only location ‘* p’
    std::cout << *p << std::endl;

    const int* const q = &num; //the pointer nor the underlying variable can be modified 
    // q = &num; // error: assignment of read-only variable ‘q’
    std::cout << *q << std::endl;

}
