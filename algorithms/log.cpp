#include <iostream>

//linear recursion that use n recursive calls 
int Pow1(int base , int expontent)
{
    if (expontent ==0)
        return 1; 
    else 
        return base * Pow1(base, expontent-1); 
}


//linear recursion that use log(n) recursive calls 
int Pow2(int base, int exponent)
{
    if (exponent ==0)
        return 1; 
    else if (exponent % 2 ==0) //if is the number is even
    {
        int y = Pow2(base, (exponent-1)/2); 
        return base*y*y; 
    }
    else 
    {
        int y = Pow2(base, exponent/2); 
        return base*y*y; 
    }



}


int main ()
{
    std::cout << Pow1(2,4) <<std::endl; 


    std::cout << Pow2(5,3) << std::endl; 
}