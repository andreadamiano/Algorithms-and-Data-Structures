#include <iostream>
#include "doubly_linked_list.h"

using E = int; 

class Sequence : public List
{
    public: 
        Iterator atIndex(int i) const; 
        int indexOf(const Iterator& iterator) const; 
        
        int indexOf(const E& element) const; 
}; 

Sequence::Iterator Sequence::atIndex(int i) const
{
    if(i<= size()/2)
    {
        Iterator it = begin();
        for (int j=0; j<i; ++j)
            ++it; //node hopping

        return it; 
    }
    else
    {
        Iterator it = end();
        for (int j=0; j<size()-i; ++j)
            --it; //node hopping

        return it; 
    }
}   


int Sequence::indexOf(const Iterator& iterator) const
{
    Iterator it = begin(); 
    int j=0; 

    while(it != iterator)
    {
        ++it; 
        ++j; 
    }

    return j; 
}

int Sequence::indexOf(const E& element) const
{
    int i=0; 

    for(Iterator it = begin(); it != end(); ++it)
    {
        if(*it == element)
            return i;  
    }

    return -1; //element not found  
}

int main ()
{
    Sequence list; 

    for (int i =0; i<5; i++)
        list.insertFront(i); 

    auto ite = list.begin();
    for (int i=0; i<5; i++)
    {
        std::cout << *ite << std::endl; 
        ++ite; 
    }

    Sequence::Iterator it = list.begin(); 
    for (int i=0; i<3; ++i)
        ++it; 

    std::cout << list.indexOf(it) << std::endl; 
    std::cout << list.indexOf(5) << std::endl; 

    std::cout << *list.atIndex(3); 
}