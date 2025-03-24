#include <iostream>

int sum(int a, int b) {
    return a + b;
}

int main() {
    // std::cout: Sends output to the console (e.g., text, numbers).
    // std::endl: Inserts a newline and flushes the buffer, ensuring all data is written to the console immediately (useful for immediate output but can slow down performance if overused).
    // <<: Stream insertion operator.
    //std is a namespace, cout is a object, and endl is a manipulator.

    // std::cout << "Hello, World!" << std::endl;

    // int num1 {5};
    // int num2 {1};

    // int result = sum(num1, num2);

    // std::cout << result << std::endl;

    // int age;
    // std::string name;

    // std::cout << "Enter your age and name: " << std::endl; 


    // std::cin >> age >> name; // Extract input into 'num'.
    // std::cout << "age: " << age << "Name: " << name << std::endl;

    // std::string name;
    // std::cout << "Enter name with space: " << std::endl;
    // // std::getline(std::cin, name);
    // std::cin >> name;
    // std::cout << "Name: " << name << std::endl;

    int num;

    std::cout << num << std::endl;
    std::cout << sizeof(num) << std::endl;
    std::cout << sizeof(int) << std::endl;

    return 0;
}
