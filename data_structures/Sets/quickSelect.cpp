#include <iostream>
#include <vector>
#include <random>


int quickSelect(std::vector<int>& vector, int k)
{
    std::random_device rd; //generate a truly random seed 
    std::mt19937 gen(rd()); //generate a random number 
    std::uniform_int_distribution<int> dis (0, vector.size()-1); 

    if (vector.size() == 1)
        return vector[0]; 

    //generate a random number 
    auto& pivot = vector[dis(gen)]; 

    //subdivide the vector into 3 subsequences 
    std::vector<int> L; 
    std::vector<int> E; 
    std::vector<int> G; 

    for (auto& element : vector)
    {
        if (element < pivot)
            L.emplace_back(element); 
        
        else if (element == pivot)
            E.emplace_back(element); 
        
        else 
            G.emplace_back(element); 
    }

    if (k < L.size())
        return quickSelect(L, k); 

    else if (k <= (L.size() + E.size())) 
        return pivot; 

    else
        return quickSelect(G, k - L.size() - E.size()); 
    
}

int main()
{
    std::vector<int> v = {7, 2, 9, 4, 1, 5, 8, 3, 6};
    int k = 9; 
    auto result = quickSelect(v, k); 
    std::cout << result ; 
}