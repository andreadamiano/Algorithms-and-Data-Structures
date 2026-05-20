def max_students(seats: list[list]):
    """
    This is an example of a bitmask DP, where each state is encoded by a bitmask
    Every row of students is treated as a single binary number 
    Bitmask is used in this case because every state depends on the previous state's entire seats disposition
    """
    m = len(seats)
    n = len(seats[0])
    validity = []

    #encode each valid position inside a bitmasks 
    for i in range(m):
        bitmask = 0
        for j in range(n):
            bitmask = (bitmask << 1) | (seats[i][j] == ".")
        validity.append(bitmask)

    #initialize dp table
    dp = [[-1] * (1 << n) for _ in range(m + 1)]  #dp[row][mask] store the max students  (the dimension of the bitmask is large enough to store all possible 2^n combinations)
    dp[0][0] = 0 #base case

    for i in range(1, m + 1): 
        row_mask = validity[i-1] #intial bitmask for that row containing all valid positions
        for j in range(1 << n): #brute forcely generate j, which represent a random bitmask to validate 
            if (j & row_mask) == j and not (j & (j >> 1)):#check that each student is placed in a valid seat and there are no adjacent students
                cnt = bin(j).count('1') #count all 1 inside the bitmask s
                for k in range(1 << n): #brute forcely generate k, which represent a random bitmask that represent the disposition of the students in the previous row 
                    #check if dp[i][j] may transit from dp[i-1][k]
                    #!(j & (k >> 1)): no students in the upper left positions
				    #!((j >> 1) & k): no students in the upper right positions
				    #dp[i - 1][k] != -1: the previous state is valid
                    if dp[i-1][k] != -1 and not (j & (k >> 1)) and not (j & (k << 1)):
                        dp[i][j] = max(dp[i][j], dp[i-1][k] + cnt)

    return max(dp[m])



if __name__ == "__main__":
    seats = [[".","#"],
                ["#","#"],
                ["#","."],
                ["#","#"],
                [".","#"]]
    print(max_students(seats))