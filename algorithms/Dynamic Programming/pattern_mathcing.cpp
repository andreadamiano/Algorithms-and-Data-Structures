#include <iostream>
#include <vector>

using namespace std; 

vector<int> buildLastFunction(const string& patter)
{
    //this function builds an array containing for each character of the pattern the last time it appers in the string 
    const int N_ASCII = 128; //n of ASCII carachters 
    vector<int> last (N_ASCII); 

    for (int i =0; i< N_ASCII; ++i)
    {
        last[i] = -1; //initialize charachter set 
    }

    for (int i =0; i<patter.size(); ++i)
        last[patter[i]] = i; 

    return last; 
}

int patterMatching(const string& text, const string& pattern)
{
    int lt = text.size(); 
    int lp = pattern.size(); 
    vector<int> last = buildLastFunction(pattern); 

    if (lp  > lt)
        return -1; 

    int j = lp -1; 
    int i = j; 
    do 
    {
        if (pattern[j] == text[i])
        {
            if (j==0)
                return i;

            else
            {
                --j; 
                --i; 
            }
        }

        else
        {
            i = i + lp - min(j, 1+ last[text[i]]);      
            j = lp-1; 
        }
    
    }while(i<=lt-1); 


    return -1; 
}

vector<int> failureFunction(const string& pattern)
{
    vector<int> fail(pattern.size()); 

    fail[0] = 0; 

    int j =0; //lenght of the previous longest suffix 
    int i = 1;
    
    while(i < pattern.size())
    {
        if(pattern[i] == pattern[j])
        {
            fail[i] = j+1; 
            ++i; 
            ++j; 
        }
        else if (j>0)
            j = fail[j-1]; 

        else
        {
            fail[i] =0; 
            ++i; 
        }
    }

    return fail; 
}

int KPPAlgorithm(const string& text, const string& pattern)
{
    vector<int> fail = failureFunction(pattern);
    int i =0; //text pointer 
    int j =0; //pattern pointer 
    while(i <text.size())
    {
        if(pattern[j] == text[i])
        {
            if(j ==pattern.size()-1)
                return i - pattern.size() +1; //found a match 
                
            else
            {
                ++i; 
                ++j; 
            }
        }
        else if (j>0)
            j = fail[j-1];
        else
            ++i;
    }

    return -1; //no match
}

int BruteForcePatternMatching(std::string& text, std::string& pattern)
{
    for (int i =0; i < text.size(); ++i)
    {
        int j=i; 
        int k=0; 
        while(text[j] == pattern[k] && k < pattern.size())
        {
            ++j; 
            ++k; 
        }
        if (k == pattern.size())
            return i; 
    }
    return -1; 
}

int main ()
{
    string pattern = "CIAO"; 
    string text = "EIII CIAO"; 
    cout << patterMatching(text, pattern) << "\n"; 
    cout << BruteForcePatternMatching(text, pattern); 
}