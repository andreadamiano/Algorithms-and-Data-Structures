#include <iostream>
#include <random>
#include <vector>
#include <random>

int arrayMax(std::vector<int>& array)
{
    int currMax; 
    for (int i=0; i< array.size(); i++)
    {
        if (currMax < array[i])
            currMax = array[i]; 
    }

    return currMax; 
}

int main ()
{
    std::vector<int> array(100); 
    std::random_device rd; //generate a truly random seed 
    std::mt19937 gen(rd()); //generate a random number 
    std::uniform_int_distribution dis (0, 100); 

    for (int& num : array)
    {
        num = dis(gen); //fill the array with random numbers
        // std::cout << num << std::endl ;
    } 
        

    std::cout << arrayMax(array); 

}