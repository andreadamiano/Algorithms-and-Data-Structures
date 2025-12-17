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
            //dp[i][j] is the cost of multiplying the matrix i times the matrix j 
            dp[i][j] = INT_MAX; //initialize upper triangular matrix to infinity

            //try all possible splits between i and and j
            for (int k=i; k<j; ++k)
            {
                //dp[i][k] + dp[k + 1][j] was the optimal cost to multiply i-k and k+1-j
                //p[i - 1] * p[k] * p[j] is the cost of multiplying the resulting matrices 
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j]; //cost to multiply this 2 matrix 
                if (cost < dp[i][j]) 
                    dp[i][j] = cost;


                for (int i =1; i<n+1; ++i)
                {
                    for (int j=1; j<n+1; ++j)
                    {   
                        std::cout << dp[i][j] << " "; 
                    }
                    std::cout << "\n"; 
                }
                std::cout << "\n";

            }

        
        }
    }
    return dp[1][n]; 
}

int BruteForce (int i, int j, const std::vector<int>& p)
{
    //stop condition 
    if (i == j)
        return 0; 

    int cost = INT_MAX; 
    int current_cost =0; 
    
    for (int k =i; k < j; ++k)
    {
        current_cost = BruteForce(i, k, p) + BruteForce(k+1, j, p) + p[i-1]*p[k]*p[j]; 
        if (current_cost < cost)
            cost = current_cost; 
    } 

    return cost; 
    
}

int main ()
{
    // vector<int> p {30, 5, 10, 20, 40, 60}; 
    // vector<int> p {30, 5, 10, 20, 40, 60, 40};
    vector<int> p {2, 10, 50, 20};

    // std::cout << matrixChainOrder(p) << "\n";
    
    std::cout << BruteForce(1, 3, p); 
    
}