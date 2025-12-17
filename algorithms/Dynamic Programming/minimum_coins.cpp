#include <iostream>
#include <vector>
#include <unordered_map>

// int min_coins(std::vector<int>& coins, int total)
// {
//     //bottom up solution
//     std::vector<int> dp(total+1, INT_MAX); //dp[i] represent the oprimal solution for the quantity i 
//     dp[0] =0; //initial condition 

//     for (int i =1; i <= total; ++i) //for a given quantity
//     {
//         for (auto coin : coins) //check using brute force every possible combination 
//         {
//             if (i - coin >=0 && dp[i - coin] != INT_MAX)
//                 dp[i] = std::min(dp[i], dp[i - coin]+1); 
//         }
//     }

//     return dp[total] == INT_MAX ? -1 : dp[total]; //f no solution was found return -1 
// }


std::unordered_map<int, int> memo; 
int min_coins(std::vector<int> coins, int total)
{
    //top down solution
    if (memo.find(total) != memo.end())
        return memo[total]; 

    if (total ==0)
        return 0; 

    if (total < 0)
        return INT_MAX; 

    int result = INT_MAX; 
    for (auto coin : coins)
    {
        int intermediate = min_coins(coins, total - coin); 

        if (intermediate != INT_MAX) //check if the subprobelm has a solution 
            result = std::min(result, intermediate +1); 
    }
    
    memo[total] = result; 
    return result; 
}


int main()
{
    std::vector<int> coins = {4,5,10}; 
    int total = 100; 

    std::cout << min_coins(coins, total); 
}