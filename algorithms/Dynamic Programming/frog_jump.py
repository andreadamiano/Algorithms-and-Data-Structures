memo = {}


def can_cross(stones: list):
    n = len(stones)

    def dp(current_position, jump):
        if current_position == n-1:
            return True
        
        if (current_position, jump) in memo:
            return memo[(current_position, jump)]
        
        jumps = {jump-1, jump, jump+1}
        for next in range(current_position+1, n):
            distance = stones[next] - stones[current_position]

            if distance > jump + 1:
                break

            if distance in jumps:
                if dp(next, distance):
                    return True
    
        memo[(current_position, jump)] = False
        return False
            

    return dp(0, 0) 


    
    dp = [[False for _ in range(n)] for _ in range(n)]
    dp[0][1] = True   #dp[i][j] denote at stone i, the frog can or cannot make jump of size j

    for i in range(1, n):  #current stone
        for j in range(0, i):   #previous stone 
            distance = stones[i] - stones[j]
            if distance < 0 or distance >= n or not dp[j][distance]:
                continue
            
            dp[i][distance] = True
            if distance -1 >= 0 :
                dp[i][distance-1] = True
            if distance +1 < n :
                dp[i][distance+1] = True
            # if i == n - 1:
            #     return True

    for row in dp:
        print(row)

    # return False


if __name__ == "__main__":
    # stones = [0,1,2,3,4,8,9,11]
    stones = [0,1,3,5,6,8,12,17]
    # stones = [0,1,3,4,5,7,9,10,12] 
    print(can_cross(stones))
