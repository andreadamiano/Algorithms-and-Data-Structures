def calculateMinimumHP(dungeon):
    lx = len(dungeon[0]) 
    ly = len(dungeon)

    dp = [[float("inf") for _ in range(lx+1)] for _ in range(ly+1)] #every state store the minHP to reach that position
    dp[ly][lx - 1] = 1
    dp[ly - 1][lx] = 1
    
    for y in range(ly-1, -1, -1):
        for x in range(lx-1, -1, -1):
            neededHp = min(dp[y+1][x], dp[y][x+1]) - dungeon[y][x]
            dp[y][x] =neededHp if neededHp > 0 else 1

    for row in dp:
        print(row)

    return dp[0][0]

    # def dfs(x, y, minHP = 0, currHp = 0):
    #     currHp += dungeon[y][x]
    #     minHP = max(-currHp, minHP)   
    #     if x == lx-1 and y == ly-1:
    #         # return max(minHP +1, max(-dungeon[0][0]+1, 1))
    #         return minHP + 1

    #     if y == ly-1 and x < lx -1:
    #         x, y = x+1, y

    #     elif x == lx-1 and y < ly -1:
    #         x, y = x, y+1
    #     else:
    #         x, y = (x, y+1) if dungeon[y+1][x] > dungeon[y][x+1] else (x+1, y)

    #     return dfs(x, y, minHP, currHp)

    # return dfs(0, 0)


if __name__ == "__main__":
    # dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
    # dungeon = [[100]]
    # dungeon = [[-3,5]]
    # dungeon = [[1],[-2],[1]]
    dungeon = [[1,-3,3],[0,-2,0],[-3,-3,-3]]
    print(calculateMinimumHP(dungeon))