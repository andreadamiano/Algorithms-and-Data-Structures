#include <iostream>
#include <random>
#include "ArraySequence.h"

using E = int; 
void BubbleSort(Sequence& s)
{
    for (int i=0; i< s.size(); ++i)
    {
        for (int j=1; j< s.size() -i; ++j)
        {
            auto prec = s.atIndex(j-1);
            auto succ = s.atIndex(j); 
            
            if(*prec> *succ)
            {
                E temp = *prec; 
                *prec = *succ; 
                *succ = temp;   

            }
        }
    }
}

void BubbleSort2 (Sequence& s)
{
    for (int i =0; i< s.size(); ++i)
    {
        auto prec = s.begin(); 
        for (int j=1; j< s.size()-i; ++j)
        {
            auto succ = prec; 
            ++succ; 
            if (*prec>*succ)
            {
                E temp = *prec; 
                *prec = *succ; 
                *succ = temp; 
            }
            ++prec; 
        }
    }
}


int main ()
{
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution dis (0,1000); 

    Sequence s; 

    //populate seuqnce 
    for (int i =0; i<99; ++i)
    {
        
        s.insertBack(dis(gen));  
    }  

    for (auto it = s.begin(); it != s.end(); ++it)
        std::cout << *it << "\n"; 

    //sorting the sequence 
    BubbleSort2(s); 

    std::cout << "\n" << "Sorted sequence" << std::endl; 
    for (auto it = s.begin(); it != s.end(); ++it)
        std::cout << *it << "\n"; 

    

}