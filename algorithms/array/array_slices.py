from collections import defaultdict

def array_slices(nums):
    n = len(nums)
    total_count = 0  
    dp = [defaultdict(int) for _ in range(n)]  #dp[i][diff] stores the number of arithmetic subsequence ending at nums[i] with common difference diff 
    
    for i in range(1, n):
        for j in range(i):
            diff = nums[i] - nums[j]
            dp[i][diff] += 1  
            if diff in dp[j]:
                dp[i][diff] += dp[j][diff]
                total_count += dp[j][diff]

    for row in dp:
        print(row)

    return total_count


if __name__ == "__main__":
    nums = [2,4,6,8,10]
    print(array_slices(nums))