#include <iostream>
#include "header.h"

int main ()
{
    SayHello();
    SayGoodbye();
    extern int num; //global variable

    std::cout << num << std::endl;
    return 0;
}