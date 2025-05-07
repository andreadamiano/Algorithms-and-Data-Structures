#include <iostream>
#include <cmath>

//7 main functions:

//constant function 
float constant (int x)
{
    int c = 2; 
    return  c;  
}


//log function 
float logaritm (int x)
{
    return log(x); 
}



//linear function 
float linear (int x)
{
    return x; 
}


//n log n function
float nlogn(int x)
{
    return x * log(x) ;  //much faster than quadratic functions, a little bit slower than linear functions
}


//quadratic function
float quadratic (int x)
{
    return pow(x, 2); 
}


float cubic (int x)
{
    return pow(x, 3); 
}


float exponential (int x)
{
    return pow (2, x); 
}

int main ()
{

    int x; 
    std::cin >> x;

    std::cout << "result: " << constant(x) << std::endl;  

    std::cout << "result: " << logaritm(x) << std::endl;   

    std::cout << "result: " << linear(x) << std::endl;  

    std::cout << "result: " << nlogn(x) << std::endl;

    std::cout << "result: " << quadratic(x) << std::endl;

    std::cout << "result: " << cubic(x) << std::endl;

    std::cout << "result: " << exponential(x) << std::endl;
}