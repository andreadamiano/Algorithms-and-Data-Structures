#include <iostream>
#include <vector>
#include <random>

//quadratic time algorithm 
std::vector<float> prefixAverages1 (std::vector<int>& X)
{
    std::vector<float> A (X.size()); //n time 

    for (int i =0; i < X.size(); i++ )
    {
        float a =0; 
        for (int j =0; j<=i; j++)
        {
            a += X[j]; 
        }
        A[i] = a/(i+1); //compute the average 
    }

    return A; 

    
}

std::vector<float> prefixAverages2 (std::vector<int>& X)
{
    std::vector<float> A (X.size()); 
    int s =0; 
    for (int i =0; i< X.size(); i++)
    {
        s += (X[i]); 
        A[i] = static_cast<float>(s) / (i+1); 
    }
    return A; 
}


int main ()
{
    std::random_device rd; 
    std::mt19937 gen(rd());  
    std::uniform_int_distribution dis(0, 100); 

    std::vector<int> X(100); 

    for (int& num : X)
    {
        num = dis(gen); //random number between 0 and 100
        std::cout << num << std::endl; 
    }

    // std::vector<float> A = prefixAverages1(X); 
    std::vector<float> A = prefixAverages2(X); 


    std::cout << "Prefix averages" << std::endl; 
    for (float& num : A)
    {
        std::cout << num << std::endl; 
    }

}