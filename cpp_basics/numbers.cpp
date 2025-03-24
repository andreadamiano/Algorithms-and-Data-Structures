#include <iostream>

int main ()
{
    int num_1 = 12;
    int num_2 = 017; //octal number
    int num_3 = 0x1A; //hexadecimal number
    int num_4 = 0b1100; //binary number

    std::cout << num_1 << std::endl;  
    std::cout << num_2 << std::endl;
    std::cout << num_3 << std::endl;
    std::cout << num_4 << std::endl;
}