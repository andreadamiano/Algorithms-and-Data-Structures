def max_profit(k: int, prices: list):
    n = len(prices)
    # at each day i can either but or sell a stock 

    # if the number of k is more then half the len of stock prices adopt a greedy approach by making every possible profitable trade  
    if k >= len(prices) // 2:
        return sum(max(0, prices[i] - prices[i-1]) for i in range(1, len(prices)))

    # removed the time variable to reduce space complexity  
    # every state depends on the precious time (t-1) state, so it's sufficient to update the dp value in place 
    buy = [-float('inf')] * (k + 1)  # represent the max number of money you can have on day i after making j transactions and currently holding a stock
    sell= [0] * (k+1) # represent the max umber of money you can have on day i after making j transactions and currently not holding a stock

    for price in prices:
        for j in range(1, k + 1):
            buy[j] = max(buy[j], sell[j-1] - price) # max capital holding the stock 
            sell[j] = max(sell[j], buy[j] + price) # max capital without holding the stock

    return sell[k]  #return the amount of money you have after k transaction without holding the stock


def max_profit(k: int, prices: list):
    """
    Non space optimized solution
    """
    n = len(prices)
    if n == 0 or k == 0:
        return 0
    
    # 3d dp array, since i have to keep track of 3 variables at each step:
    # whats the day 
    # how many transaction have i used
    # am i currently holding a stock
    # at each state we store the maximum profit
    dp = [[[0, 0] for _ in range(k + 1)] for _ in range(n)]

    # initialize first day 
    for j in range(1, k + 1):
        dp[0][j][0] = 0           
        dp[0][j][1] = -prices[0]


    for i in range(1, n):
        for j in range(1, k + 1):
            # STATE: NOT HOLDING STOCK
            # Either we didn't have it yesterday, 
            # OR we had it and we are selling it today.
            dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1] + prices[i])
            
            # STATE: HOLDING STOCK
            # Either we were already holding it from yesterday,
            # OR we buy it today (using profit from the PREVIOUS transaction j-1)
            dp[i][j][1] = max(dp[i-1][j][1], dp[i-1][j-1][0] - prices[i])


    print(dp)

    return dp[n-1][k][0]

if __name__ == "__main__":
    k = 2
    prices = [3,2,6,5,0,3]
    print(max_profit(k, prices))