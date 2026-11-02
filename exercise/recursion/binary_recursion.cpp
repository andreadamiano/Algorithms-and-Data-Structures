#include <iostream>
#include <vector>
#include <tuple> //for std::pair 

//When an algorithm makes two recursive calls, we say that it uses binary recursion.

int Binary_sum( std::vector<int>& array, int init, int final)
{
    if (final ==1)
        return array[init]; 
    
    return Binary_sum(array, init, final/2) + Binary_sum(array, init+final/2, final/2); 
}

int BinaryFibbonacci (int k)
{
    if( k<= 1)
        return k; 
    else
        return BinaryFibbonacci(k-1) + BinaryFibbonacci(k-2); 
}

// std::tuple<int, int>  LinearFibbonacci (int k)
// {
//     if (k<=1)
//         return std::make_tuple(k,0); 
//     else   
//     {
//         auto prev = LinearFibbonacci(k-1); //get previous values 
//         return std::make_tuple(std::get<0> (prev) + std::get<1> (prev), std::get<0> (prev)); 

//     }
// }


std::vector<int> LinearFibbonacci (int k)
{
    if (k <=1)
        return {k,0}; 
    else
    {
        std::vector<int> prev = LinearFibbonacci(k-1); 
        return {prev[0] + prev[1] , prev[0]}; 
    }
}


int main ()
{
    std::vector<int> array {1,2,3,4,5}; 

    int sum = Binary_sum(array, 0, array.size()); 

    std::cout << sum << std::endl; 

    // int k = BinaryFibbonacci(3); 
    auto k = LinearFibbonacci(3); 

    // std::cout << std::get<0> (k) << std::endl; 

    std::cout << k[0] <<std::endl; 

}