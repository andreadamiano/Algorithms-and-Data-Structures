#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

//inefficient recursive algorithm
bool isUnique1(std::vector<int>& array, int start, int end)
{
    if (start>end)
        return true; 

    if (!isUnique1(array, start, end-1))
        return false; 

    if (!isUnique1(array, start+1, end))
        return false; 
    
    return (array[start] != array[end]); 

}



//better iterative algorithm 
bool isUnique2 (std::vector<int>& array, int start, int end) //where end is the size of the array 
{
    if (start > end)
        return true; 

    for (int i =start; i<end-1; i++)
        for (int j=i+1; j<end; j++)
            if(array[i] == array[j])
                return false; 
    
    return true; 
}


//even better algorithm 
bool isUniqueSort(std::vector<int>& array, int start, int end)
{
    if(start>end)
        return true; 
    
    std::vector<int> copy(array); //create a deep copy, invoking the copy constructor 
    sort(copy.begin() +start, copy.begin() +end); //sort the array 

    for (int i =start; i<end-1; i++)
    {
        if (copy[i] == copy[i+1])
            return false; 
    }
    return true; 
}   



int main ()
{
    std::vector<int> array (9999); 
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,10000); 

    //populate array
    for (int& num : array)
    {
        num = dis(gen); 
    }

    std::cout << isUniqueSort(array, 0, array.size());  //true = 1, false = 0 

}