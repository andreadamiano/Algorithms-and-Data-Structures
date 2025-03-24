#include <iostream>
#include <vector>
#include <random>
// #include "LinkedStack.h"
#include "ArrayStack.h"


template<typename E>
void reverse(std::vector<E>& array)
{
    ArrayStack<E> stack(array.size()); //initialize a stack of the size of the array
    for (int i =0; i< array.size(); i++)
    {
        stack.push(array[i]); 
    }
    for (int i=0; i<array.size(); i++)
    {
        array[i] = stack.top(); 
        stack.pop(); 
    }
}


int main ()
{

    std::vector<int> array (1000); 

    //populate array
    for (int i=0; i<1000; i++)
    {
        array[i] =i; 
    }

    reverse(array); 

    for(int i=0; i<1000; i++)
    {
        std::cout << array[i] << "\n"; 
    }


    
}