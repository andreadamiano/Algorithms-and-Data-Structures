#include <iostream>
#include <vector> 
#include <chrono>

using namespace std; 

int longestCommonSubsequence(const std::string& X, const std::string& Y)
{ 
    int lx = X.size(); 
    int ly = Y.size(); 
    vector< vector<int> > dp(lx+1, vector<int> (ly+1, 0));

    auto start = chrono::high_resolution_clock::now();

    for (int i =1 ; i< lx+1; ++i)
    {
        for (int j=1; j< ly+1; ++j)
        {
            if(X[i-1]==Y[j-1])
                dp[i][j] = dp[i-1][j-1] +1; 

            else    
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]); 
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
    cout << "duration: " << chrono::duration_cast<chrono::milliseconds> (end-start) << "\n"; 
    cout << "\n"; 


    return dp[lx][ly]; 

}

int main ()
{
    std::string X = "ABXCDEFGHIJKLMNOPQRSTUV"; 
    std::string Y = "BCDEFXGHYIJKZLMNOPQR"; 

    cout << longestCommonSubsequence(X, Y); 

}