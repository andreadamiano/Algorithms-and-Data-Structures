#include <iostream>
#include <vector>
#include <random>



void Merge (std::vector<int>& array, int left, int mid, int right)
{
    int n1 = mid - left+1; //size of the left subarray 
    int n2 = right -mid; //size of the right subarray 

    //create temporary arrays 
    std::vector<int> L(n1), R(n2); 

    //copy data to temporary arrays 
    for (int i =0; i<n1; i++)
    {
        L[i] = array[left +i]; 
    }
    for (int j =0; j<n2; j++)
    {
        R[j] = array[mid +j+1];  
    }

    //merge temporary arrays
    int i=0, j=0, k=left; 
    while(i<n1 && j<n2)
    {
        if(L[i] < R[j]) //check which element is bigger 
        {
            array[k] = L[i]; 
            i++; 
        }
        else 
        {
            array[k] = R[j]; 
            j++; 
        }
        k++; 
    }


    //copy remaining elements 
    while (i<n1)
    {
        array[k] = L[i]; 
        i++; 
        k++; 
    }
    while(j<n2)
    {
        array[k] = R[j]; 
        j++; 
        k++; 
    }

}

void MergeSort (std::vector<int>& array, int left , int right)
{
    if (left<right)
    {
        int mid = left +(right - left)/2; 
        MergeSort(array, left, mid); //sort left half
        MergeSort(array, mid+1, right); //sort right half
        Merge(array, left, mid, right); 
    }
}

bool areDisjoint(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
{
    //initialize pointers
    int i=0, j=0, k=0; 


    //move the pointer pointing to the smallest element 
    while(i<A.size() && j<B.size() && k<C.size() )
    {
        if (A[i] == B[j] && B[j] == C[k])
        {
            return true; //the 3 sets are not disjoint 
        }
        else
        {
            if (A[i] <= B[j] && A[i] <= C[k])
                i++; 
            if (B[j] <= A[i] && B[j] <= C[k])
                j++; 
            if (C[k] <= A[i] && C[k] <= B[j])
                k++; 
        }

    }
     return true; 
}


int main ()
{
    std::vector<int> A (1000); 
    std::vector<int> B (1000); 
    std::vector<int> C (1000); 

    std::random_device gen ; 
    std::mt19937 rd(gen());
    std::uniform_int_distribution<> dis(0,999);  

    //populate arrays
    for (int i =0; i<1000; i++)
    {

        A[i] = dis(gen);
        B[i] = dis(gen);
        C[i] = dis(gen);
    }


    //sort the arrays
    MergeSort(A, 0, 999); 
    MergeSort(B, 0, 999); 
    MergeSort(C, 0, 999); 

    //checking if are disjoint
    std::cout << areDisjoint(A,B,C); 


}