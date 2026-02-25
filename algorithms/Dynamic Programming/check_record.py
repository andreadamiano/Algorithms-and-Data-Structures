def check_record_bu(n):
    """Top-down solution"""
    memo = [[[-1 for _ in range(3)] for _ in range(2)] for _ in range(n) ] # temp[cur_ind][count_a][count_l] , curr_ind represnet the current day being processed 
    print(memo)
    MOD: int = 10**9 + 7
     
    def dp(curr_i, curr_a, curr_l):
        if curr_i == n:
            return 1
        
        if memo[curr_i][curr_a][curr_l] != -1:
            return memo[curr_i][curr_a][curr_l] 
        
        # explore A, P, L in sequence
        with_a_next = dp(curr_i +1, curr_a +1, 0) if curr_a < 1 else 0
        with_p_next = dp(curr_i+1, curr_a, 0)
        with_l_next = 0 if curr_l == 2 else dp(curr_i+1, curr_a, curr_l+1)
        total = (with_a_next + with_p_next + with_l_next) % MOD
        memo[curr_i][curr_a][curr_l] = total 
        print(memo)
        return total
    
    return dp(0, 0, 0)

def check_record(n):
    """Bottom-up solution"""
    MOD = 1000000007

    dp_last: list[list[int]] = [[0 for _ in range(3)] for _ in range(2)]  # previous state
    dp_current: list[list[int]] = [[0 for _ in range(3)] for _ in range(2)]  # current state 

    dp_last[0][0] = 1  # empty string

    for _ in range(n):
        for count_a in range(2):
            for count_l in range(3):
                # choose "P"
                dp_current[count_a][0] = (dp_current[count_a][0] + dp_last[count_a][count_l]) % MOD
                # choose "A"
                if count_a == 0:
                    dp_current[count_a + 1][0] = (dp_current[count_a + 1][0] + dp_last[count_a][count_l]) % MOD
                # Choose "L"
                if count_l < 2:
                    dp_current[count_a][count_l + 1] = (
                        dp_current[count_a][count_l + 1] + dp_last[count_a][count_l]
                    ) % MOD
        
        print(dp_current)
        dp_last = dp_current  # Reference current to previous
        dp_current = [[0 for _ in range(3)] for _ in range(2)]  # make new current

    # Sum up the counts for all combinations of length 'n' with different count_a and count_l.
    res: int = sum(dp_last[count_a][count_l] for count_a in range(2) for count_l in range(3)) % MOD

    return res

if __name__ == "__main__":
    n = 2
    print(check_record(n))
    print(check_record_bu(n))