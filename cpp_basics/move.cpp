#include <iostream>
#include <utility>
#include <string>

int main ()
{
    std::string source = "ciao come va ?"; 
    std::string destination; 
    
    destination = std::move(source); //move is a casting to a rvalue reference

    std::cout << destination; 
    std::cout << source; 



}