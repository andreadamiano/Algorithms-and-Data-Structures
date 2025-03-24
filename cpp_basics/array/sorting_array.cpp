#include <iostream>

//insertion-sort algorithm
void insertionSort(int* array, int n) //non-decreasing order 
{
    for (int i=1; i<n; i++)
    {   
        int current = array[i]; //save current element in the array
        int j= i-1; 

        while((j>=0) &&(array[j]>current))
        {
            array[j+1] = array[j]; //move element to the right 
            j--; 
        }
        array[j+1] = current; //move the current element to the left 
    }
}

int main ()
{
    int array [] {9,3,63,14,74,2,5,75,4,0};

    insertionSort(array, 10);

    for (int i=0; i<10; i++)
    {
        std::cout << array[i] << std::endl;
    }
}