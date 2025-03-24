#include <thread>
#include <iostream>

void hello()
{
    std::cout << "Hello Word"; 
}

int main()
{
    std::thread t(hello); 
    t.join(); 
}