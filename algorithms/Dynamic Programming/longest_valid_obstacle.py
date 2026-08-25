import bisect

def longest_valid_obstacle(obstacles: list):
    dp = [0]
    n = len(obstacles)
    result = [0] * n

    for  i, obstacle in enumerate(obstacles):
        index = bisect.bisect_right(dp, obstacle)

        if index == len(dp):
            dp.append(obstacle)

        else:
            dp[index] = min(obstacle, dp[index]) #the the min to allow for longer increasing subsequences

        result[i] = index 

    print(dp)

    return result

if __name__ == "__main__":
    obstacles = [1,2,3,2]
    obstacles = [3,1,5,6,4,2]
    print(longest_valid_obstacle(obstacles))
    