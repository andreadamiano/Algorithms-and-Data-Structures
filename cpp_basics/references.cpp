#include <iostream>

void modifyValue(int& ref) {
    ref =  ref * 2; // Multiply the original variable's value by 2
}

void modifyValue_2(int* ptr) {
    *ptr = *ptr * 2; // Multiply the original variable's value by 2
}

int main() {
    int x = 10;
    int& y = x; // 'y' is a reference to 'x', once initialized, it cannot be changed (unlike pointers)

    int *p = &x;
    
    std::cout << "Original x: " << x << std::endl; // 10
    y = 20; // Modifies 'x' through 'y'
    std::cout << "Modified x through y: " << x << std::endl; // 20
    
    modifyValue(x); // Pass 'x' by reference
    std::cout << "x after modifyValue: " << x << std::endl; // 40

    *p = 50;
    std::cout << "x modify with the pointer: " << x << std::endl; // 50

    modifyValue_2(&x); // Pass 'x' by pointer
    std::cout << "x after modifyValue_2: " << x << std::endl; // 40

    
    
    return 0;
}