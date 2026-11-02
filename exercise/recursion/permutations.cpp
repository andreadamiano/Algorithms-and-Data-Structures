#include <iostream>
#include <vector>


void Permutations(std::vector<char>& S, std::vector<char>& U)
{
    if (U.empty())
    {
        for (auto& ch : S)
            std::cout << ch << " "; 
        
        std::cout << "\n"; 
        return; 
    }

    for (int i = 0; i< U.size(); ++i)
    {
        auto element = U[i]; 
        S.emplace_back(element); 
        U.erase(U.begin() + i); 

        Permutations(S, U); 

        S.pop_back(); 
        U.insert(U.begin()+ i, element); 
    }

}


int main ()
{
    std::vector<char> U = {'a', 'b', 'c'}; 
    std::vector<char> S; 
    Permutations(S, U); 
}