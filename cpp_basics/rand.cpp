#include <iostream>
#include <cstdlib>

int main ()
{
    srand(time(NULL));  //seed the rand function 

    int b (10);
    int a(4);

    int num = a+ rand() %(b-a+1) ; //generate a random nnunmber between a and b 

    std::cout << num << std::endl;
    std::cout << time (NULL) << std::endl; 
    std::cout << "RAND_MAX: " << RAND_MAX << std::endl; //max value of the rand function 



}