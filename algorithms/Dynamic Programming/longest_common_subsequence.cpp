#include <iostream>
#include <vector> 
#include <chrono>
#include <unordered_map>
#include <tuple>
#include <functional>

using namespace std; 

//custom hash functor 
struct CustomHAsh
{
    static constexpr size_t offset = 14695981039346656037ULL; //large prime number (ULL stands for unsigned long long, 64 bit integer) (ULL is used to force the liter to be a 64 bit unsigned long long , the literal is the number used to be assigned to the type)
    static constexpr size_t alpha = 1099511628211ULL; //another large prime number 
    std::hash<int> hasher; 

    size_t operator() (const std::pair<int, int>& p) const
    {
        size_t h1 = hasher(p.first); 
        size_t h2 = hasher(p.second); 

        //combien hashes (boost implementation)
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};


std::unordered_map<std::pair<int, int>, int, CustomHAsh> memo; 
int longestCommonSubsequence(const std::string& X, const std::string& Y, int xi, int yi)
{
    //top down approach

    //base case 
    if (xi < 0 || yi < 0)
        return 0; 

    if (memo.find({xi, yi}) != memo.end())
        return memo[{xi, yi}];   

    int result =0; 
    if (X[xi] == Y[yi])
    {
        result = longestCommonSubsequence(X, Y, xi -1, yi -1) +1; 
    }
    else
    {
        result = std::max(longestCommonSubsequence(X, Y, xi -1, yi), longestCommonSubsequence(X, Y, xi, yi -1)); 
    }

    memo[{xi, yi}] = result; 
    return result; 

}

int longestCommonSubsequence(const std::string& X, const std::string& Y)
{ 
    int lx = X.size(); 
    int ly = Y.size(); 
    vector< vector<int> > dp(lx+1, vector<int> (ly+1, 0)); //initialize to all zero 

    auto start = chrono::high_resolution_clock::now();

    //dp[i][j] represent the LCS betwen the first i characters of the first string and the first j characters of the second string 
    for (int i =1 ; i< lx+1; ++i)
    {
        for (int j=1; j< ly+1; ++j)
        {
            //if characters match 
            if(X[i-1]==Y[j-1])
                dp[i][j] = dp[i-1][j-1] +1; //enxtend the longest subsequence 

            else    
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);//take the longest common subsequence either ignoring the last element of the first or the second string    
        }
    }
    auto end = chrono::high_resolution_clock::now(); 

    for (int i =1 ; i< lx+1; ++i)
    {
        for (int j=1; j< ly+1; ++j)
        {
           cout << dp[i][j] << " "; 
        }
        cout << "\n"; 
    }

    //print the longest common subsequence starting from the dp table 
    std::string buffer; 
    int i = lx; 
    int j = ly; 
    while(i >0 && j > 0)
    {
        if (X[i-1] == Y[j-1])
        {
            buffer.insert(buffer.begin(), X[i-1]);
            --i; 
            --j; 
        }
        else 
        {
            dp[i-1][j] > dp[i][j-1] ? --i : --j; 
        }
    }

    cout << buffer << "\n"; 
    cout << "duration: " << chrono::duration_cast<chrono::milliseconds> (end-start) << "\n"; 
    cout << "\n"; 


    return dp[lx][ly]; 

}

int main ()
{
    std::string X = "ABXCDEFGHIJKLMNOPQRSTUV"; 
    std::string Y = "BCDEFXGHYIJKZLMNOPQR"; 

    cout << longestCommonSubsequence(X, Y) << "\n"; 
    cout << "top down approach: " << longestCommonSubsequence(X, Y, X.size()-1, Y.size()-1); 

}