#include <iostream>

int main ()
{
    // int num = 10;
    // int num_2 = 7; 

    // int num_3 = num / num_2; // 1
    // float num_4 = num / num_2; // 1.0
    // float num_5 = (float) num / (float) num_2; // 1.42857
    // float num_6 = float(num/num_2); // 1.0

    // std::cout << num_3 << std::endl;
    // std::cout << num_4 << std::endl;
    // std::cout << num_5 << std::endl;
    // std::cout << num_6 << std::endl;

    //static casting  (Converting between compatible types)
    double d = 3.14;
    int i = static_cast<int>(d);  // Truncate the decimal

    std::cout << d << std::endl;
    std::cout << i << std::endl;


    //const casting (Remove the const qualifier)
    const int a = 42;
    int* b = const_cast<int*>(&a);  // Removes constness

    *b = 43;

    std::cout << a << std::endl;
    std::cout << *b << std::endl;



}