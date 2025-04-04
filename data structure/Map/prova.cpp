#include <list>
#include <iostream>

int main ()
{
    std::list<int> list; 

    list.push_back(1); 
    list.push_back(2); 
    list.push_back(3); 
    list.push_back(4); 
    list.push_back(5); 

    std::list<int>::iterator it; 

    std::cout << it->begin();
}