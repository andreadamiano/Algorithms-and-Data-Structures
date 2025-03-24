#include <iostream>
#include <vector>
//linear recursion: a function is defined so that it makes at most one recursive call each time it is invoked.

//tail recursion: an algorithm uses tail recursion if it uses linear recursion and the algorithm makes a recursive call as its very last operation.

int sum (std::vector<int>& array, int n)
{
    if (n ==1)
        return array[0]; 
    else 
        return sum (array, n-1) + array[n-1]; 
}

void reverse (std::vector<int>& array, int init, int final)
{
    if (init < final)
    {
        int temp = array[final]; 
        array[final] = array[init];
        array[init] = temp;  
        reverse(array, init+1, final-1); 
    }
}

void non_recursive_reverse(std::vector<int>& array, int init, int final)
{   
    while(init<final)
    {
        int temp = array[final]; 
        array[final] = array[init];
        array[init] = temp;  
        init ++; 
        final --; 
    }
}


int main ()
{
    std::vector<int> array {1,2,3,4}; 
    int summation = sum(array, array.size()); 

    std::cout << "sum: " << summation << std::endl; 


    non_recursive_reverse(array, 0, array.size()-1); 

    for (int i=0; i<array.size(); i++)
    {
        std::cout << array[i] << std::endl; 
    }
}

