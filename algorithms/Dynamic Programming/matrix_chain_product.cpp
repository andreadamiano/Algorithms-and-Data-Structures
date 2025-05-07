#include <iostream>
#include <vector>
#include <climits>

using namespace std; 

//compute the minimum number of mulitplications required 
int matrixChainOrder(const vector<int>& p)
{
    int n = p.size()-1; //number of matrix 
    vector<vector <int> > dp (n+1, vector<int>(n+1, 0)); 
    
    for (int j=2; j< n+1; ++j)
    {
        for (int i=j-1; i >= 1; --i)
        {
            dp[i][j] = INT_MAX; //initialize upper triangular matrix to infinity

            //try all possible splits between i and and j
            for (int k=i; k<j; ++k)
            {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (cost < dp[i][j]) 
                    dp[i][j] = cost;
            }

        
        }
    }

    for (int i =1; i<n+1; ++i)
    {
        for (int j=1; j<n+1; ++j)
        {
            std::cout << dp[i][j] << " "; 
        }
        std::cout << "\n"; 
    }
    std::cout << "\n";

    return dp[1][n]; 
}


int main ()
{
    // vector<int> p {30, 5, 10, 20, 40, 60}; 
    vector<int> p {30, 5, 10, 20, 40, 60, 40};
    std::cout << matrixChainOrder(p); 
}