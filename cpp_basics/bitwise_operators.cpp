#include <iostream>
#include <bitset> 

int main ()
{

    // Bitwise complement operator
    int num = 10; 
    int num_2 = ~num; 
    std::bitset<32> bits = num_2;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_2 = num;  // Prints the bits of the integer in 32 bits

    std::cout << "complement" << std::endl;
    std::cout << bits_2 << std::endl;
    std::cout << bits << std::endl;

    // Bitwise and operator
    int num_3 = 10;
    int num_4 = 12;
    int num_5 = num_3 & num_4;

    std::bitset<32> bits_3 = num_3;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_4 = num_4;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_5 = num_5;  // Prints the bits of the integer in 32 bits

    std::cout << "and" << std::endl;
    std::cout << bits_3 << std::endl;
    std::cout << bits_4 << std::endl;
    std::cout << bits_5 << std::endl;

    // Bitwise exclusive-or
    int num_6 = 10;
    int num_7 = 12;
    int num_8 = num_6 ^ num_7; //returns 0 if the bits are the same 1 if they are different 

    std::bitset<32> bits_6 = num_6;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_7 = num_7;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_8 = num_8;  // Prints the bits of the integer in 32 bits

    std::cout << "exclusive or" << std::endl;
    std::cout << bits_6 << std::endl;
    std::cout << bits_7 << std::endl;
    std::cout << bits_8 << std::endl;

    // Bitwise inclusive-or
    int num_9 = 10;
    int num_10 = 12;
    int num_11 = num_9 | num_10; //returns 1 if at least one of the bits is 1

    std::bitset<32> bits_9 = num_9;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_10 = num_10;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_11 = num_11;  // Prints the bits of the integer in 32 bits

    std::cout << "inclusive or" << std::endl;
    std::cout << bits_9 << std::endl;
    std::cout << bits_10 << std::endl;
    std::cout << bits_11 << std::endl;


    // Bitwise left shift
    int num_12 = 10;
    int num_13 = num_12 << 1; //shifts the bits to the left by 1

    std::bitset<32> bits_12 = num_12;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_13 = num_13;  // Prints the bits of the integer in 32 bits

    std::cout << "left shift" << std::endl;
    std::cout << num_13  << std::endl;
    std::cout << bits_12 << std::endl;
    std::cout << bits_13 << std::endl;

    // Bitwise right shift
    int num_14 = 10;
    int num_15 = num_14 >> 5; //shifts the bits to the right by 1

    std::bitset<32> bits_14 = num_14;  // Prints the bits of the integer in 32 bits
    std::bitset<32> bits_15 = num_15;  // Prints the bits of the integer in 32 bits

    std::cout << "right shift" << std::endl;
    std::cout << num_15  << std::endl;
    std::cout << bits_14 << std::endl;
    std::cout << bits_15 << std::endl;

    //negative number 
    int num_16 = -10;

    std::bitset<32> bits_16 = num_16;  // Prints the bits of the integer in 32 bits

    std::cout << "negative number" << std::endl;
    std::cout << bits_16 << std::endl;
    std::cout << ~num_16 << std::endl;


    //int overflow 
    int num_17 = 2147483648; // 2^31

    std::bitset<32> bits_17 = num_17;  // Prints the bits of the integer in 32 bits
    
    std::cout << "int overflow" << std::endl;
    std::cout << bits_17 << std::endl;
    std::cout << num_17 << std::endl;





}