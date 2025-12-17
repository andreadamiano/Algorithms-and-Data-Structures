#include <iostream>
#include <vector>


std::vector<int> failureFunction(const std::string& pattern)
{
    //for each substring find the longest prefix that is also a subfix   
    int i = 1; 
    int j = 0; 
    std::vector<int> failure(pattern.size(), 0); 
    failure[0] =0; 

    while(i < pattern.size())
    {
        if (pattern[i] == pattern[j])
        {
            failure[i] = j+1;
            ++i; 
            ++j; 
        }
        else if (j > 0)
        {
            j = failure[j-1]; //go to the longest prefix/subfix of the shorter substring  
        }
        else
        {
            failure[i] = 0; 
            i += 1; 
        }   
    }
    return failure; 

}


int mathchingAlgorithm(std::string& text, std::string& pattern)
{
    int lt = text.size(); 
    int lp = pattern.size(); 
    std::vector<int> failure = failureFunction(pattern); 
    int i =0; 
    int j =0; 

    while (i < lt)
    {
        if (pattern[j] == text[i])
        {
            if (j == lp -1)
                return i -lp + 1; 

            ++i; 
            ++j;
        }

        else if (j > 0)
        {
            j = failure[j-1];  
        }
        else
        {
            ++i; 
        }

    }
    return -1; 
    
}


int main()
{
    // std::string pattern = "abacab";
    std::string pattern = "CIAO";  
    std::string text = "EIII CIAO";
    std::vector<int> failure =  failureFunction(pattern); 

    for(int i =0; i < failure.size(); ++i)
        std::cout << failure[i] << " "; 

    std::cout << "\n" << mathchingAlgorithm(text, pattern) << "\n"; 

}