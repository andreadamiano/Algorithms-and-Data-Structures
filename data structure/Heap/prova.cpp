#include <iostream>
#include <vector>
#include <random>
#include "Heap.h"


int main ()
{
    Heap h1, h2;
    
    h1.addLast(1);
    h1.addLast(2);
    h1.addLast(3);

    h2.addLast(4);
    h2.addLast(5);
    h2.addLast(6);

    // std::cout << *(h1.Root()) << "\n"; 
    // std::cout << *(h1.Root().left()) << "\n";
    // std::cout << *(h1.Root().right()) << "\n";

    // std::cout << *(h2.Root()) << "\n"; 
    // std::cout << *(h2.Root().left()) << "\n";
    // std::cout << *(h2.Root().right()) << "\n";

    Heap h(0, h1 , h2); 

    std::cout << "Size: " << h.size() << "\n"; 

    std::cout << *(h.Root()) << "\n"; 

    std::cout << *(h.Root().left()) << "\n";
    std::cout << *(h.Root().left().left()) << "\n";
    std::cout << *(h.Root().left().right()) << "\n";

    std::cout << *(h.Root().right()) << "\n";
    std::cout << *(h.Root().right().left()) << "\n";
    std::cout << *(h.Root().right().right()) << "\n";

}