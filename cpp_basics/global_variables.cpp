#include <iostream>

static int num = 10; // Global variable, static means that the global variables is accessible only within this file

int main ()
{
    // int num = 20; // Local variable
    std::cout << num << std::endl; // 20
}