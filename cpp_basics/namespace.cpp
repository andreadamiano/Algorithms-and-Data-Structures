// #include <iostream>

// namespace prova 
// {
//     int sum(int a, int b) {
//         return a + b;
//     }
// }

// int main ()
// {
//     int num1 {5};
//     int num2 {1};

//     int result = prova::sum(num1, num2);
//     std::cout << result << std::endl;
// }

// #include <iostream>

// // First definition of MyNamespace
// namespace MyNamespace {
//     void func1() {
//         std::cout << "func1 from MyNamespace" << std::endl;
//     }
// }

// // Second definition of MyNamespace (same name, different location)
// namespace MyNamespace {
//     void func2() {
//         std::cout << "func2 from MyNamespace" << std::endl;
//     }
// }

// int main() {
//     MyNamespace::func1();  // Calling func1
//     MyNamespace::func2();  // Calling func2
//     return 0;
// }

#include <iostream>

// First definition of MyNamespace
namespace MyNamespace {
    void func1() {
        std::cout << "func1 from MyNamespace" << std::endl;
    }
}

// Second definition of MyNamespace (same name, same scope)
namespace MyNamespace {
    void func2() {
        std::cout << "func2 from MyNamespace" << std::endl;
    }
}

using namespace MyNamespace;
using MyNamespace::func1;

int main() {
    MyNamespace::func1();  // Calling func1
    MyNamespace::func2();  // Calling func2

    func1();  // Calling func1 without the namespace
    return 0;
}

