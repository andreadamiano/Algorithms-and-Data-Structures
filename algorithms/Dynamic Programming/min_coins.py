def min_coins(coins, total):
    dp = [float("inf") for _ in range(total+1)]
    dp[0] = 0

    for i in range(1, total+1):
        for coin in coins:
            if i-coin >= 0 and dp[i-coin] != float("inf"):
                dp[i] = min(dp[i], dp[i-coin] +1)

    return dp[-1]


if __name__ == "__main__":
    coins = [4, 5, 10]
    total = 100
    print(min_coins(coins, total))