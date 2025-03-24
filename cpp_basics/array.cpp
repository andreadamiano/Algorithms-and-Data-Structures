#include <iostream>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    char c[ ] = {'c', 'a', 't'};
    char* p = c; // p points to c[0]
    // char *p1 = &c; // error: cannot convert ‘char (*)[3]’ to ‘char*’ in initialization
    char* q = &c[0]; // q also points to c[0]
    // std::cout << c[2] << p[2] << q[2] << std::endl; // outputs “ttt”
    // std::cout << *p << std::endl; 
    // std::cout << p << std::endl;
    // std::cout << (void*)p << std::endl;
    // std::cout << p[3] << std::endl; 

    int array [4]  = {1, 2, 3, 4};

    int length = sizeof(array) / sizeof(array[0]);  // Divide total size by size of one element
    std::cout << "Length of the array: " << length << std::endl;
    std::cout << "Size of the array: " << sizeof(array) << std::endl;
    std::cout << "Size of one element: " << sizeof(array[0]) << std::endl;





    return 0;
}

