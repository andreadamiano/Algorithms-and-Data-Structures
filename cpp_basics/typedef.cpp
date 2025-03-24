#include <iostream>

typedef int* IntPtr;

int main ()
{
    int num = 10;
    IntPtr p = &num;

    std::cout << *p << std::endl;
}