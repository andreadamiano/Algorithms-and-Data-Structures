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

    //static casting  (it performs compile time checking)
    // double d = 3.14;
    // int i = static_cast<int>(d);  // Truncate the decimal

    // std::cout << d << std::endl;
    // std::cout << i << std::endl;


    //dynamic casting (performs runtime checkinig)
    class Base { virtual void foo() {} };
    class Derived : public Base {};

    Base* b = new Derived;
    Derived* d = dynamic_cast<Derived*>(b);  // Safe downcast


    //const casting (Remove the const qualifier)
    // const int a = 42;
    // int* b = const_cast<int*>(&a);  // Removes constness

    // *b = 43;

    // std::cout << a << std::endl;
    // std::cout << *b << std::endl;


    //reinterpret cast (used to directly mannipulate memory)
    struct Data {
        int x = 42;
        double y = 3.14;
    };

    Data obj;
    const char* byteView = reinterpret_cast<const char*>(&obj); //this reinterprets the memory occupied by the object as an array of char 

    for (size_t i = 0; i < sizeof(obj); i++) 
    {
        std::cout << std::hex << (int)byteView[i] << ' '; // Prints raw bytes
    }; 
    std::cout << "\n"; 

    
    int num = 0x12345678;
    const char* bytes = reinterpret_cast<const char*>(&num);
 
    //this will print each byte as an ASCII character
    for (int i =0 ; i< 4; ++i) 
    {
        if (*(bytes+i) <= 32  || *(bytes+i) >= 126)
            std::cout << "?" ; 
        else
            std::cout << *(bytes +i);  
    }
}