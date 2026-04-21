def assign_jobs(n: int, costs: list[list]):
    dp = [[float("inf")] * (1<<n) for _ in range(n+1)]  #dp[i][mask] represent the min cost to allocte ith jobs to a set of workers
    dp[0][0] = 0  #assigning zero jobs to zero workers costs zero 

    for i in range(1, n+1): #assign the ith job
        for mask in range(1<<n): #try the possible set of workers from which to add another worker
            if dp[i-1][mask] == float("inf"):
                continue
            for j in range(n):
                #try to assign the jth worker to the ith job
                if not (mask & (1<<j)): #check if the worker is not currently already working
                    new_mask = mask | (1<<j)
                    dp[i][new_mask] = min(dp[i-1][mask] + costs[j][i-1],  dp[i][new_mask]) 

    return dp[-1][-1]

if __name__ == "__main__":
    n = 4
    costs = [
        [9, 2, 7, 8],
        [6, 4, 3, 7],
        [5, 8, 1, 8],
        [7, 6, 9, 4],
    ] #costs[i][j] is the cost of assigning the ith person to the jth job
    print(assign_jobs(n, costs))