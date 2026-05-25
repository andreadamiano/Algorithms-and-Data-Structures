# def cherry_picking(grid: list[list]):
#     """Memoization solution"""
#     steps = [-1, 0, 1]
#     cols = len(grid[0])
#     rows = len(grid)
#     cache = {}

#     def dp(row, col1, col2):
#         if (row, col1, col2) in cache:
#             return cache[(row, col1, col2)]

#         if col1 < 0 or col1 > cols-1 or col2 < 0 or col2 > cols-1 or col1 == col2:
#             return 0
        
#         if row == rows-1:
#             return grid[row][col1] + grid[row][col2]

#         result = 0
#         for step1 in steps:
#             for step2 in steps:
#                 result = max(result, dp(row+1, col1 + step1, col2 + step2)) #sum the cherry currently being picked and the cherry that will be picked in the future

#         cache[(row, col1, col2)] = grid[row][col1] + grid[row][col2] + result #sum the cherry currently being picked and the cherry that will be picked in the future
#         return cache[(row, col1, col2)] 
    
#     return dp(0, 0, cols-1)


def cherry_picking(grid: list[list]):
    """Bottom up solution"""
    cols = len(grid[0])
    rows = len(grid)
    steps = [-1, 0, 1]
    prev_dp = [[0] * cols for _ in range(cols)]

    for row in reversed(range(rows)): #iterate from the bottom up
        curr_dp = [[0] * cols for _ in range(cols)] #empty initialize the current dp table

        #iterate over all possible column combinations (greedy approach dont consider overlapping path or the same columns)
        for col1 in range(cols-1):    
            for col2 in range(col1+1, cols):
                
                # compute the current picked up cherry simulating every possible previous combination given the current choosen combinatin of columns
                for step1 in steps:
                    for step2 in steps:
                        if col1+step1>=0 and col2+step2 <cols:
                            curr_dp[col1][col2] = max(curr_dp[col1][col2], prev_dp[col1+step1][col2+step2] + grid[row][col1] + grid[row][col2])
                
        prev_dp = curr_dp

    return curr_dp[0][cols-1] #the solution is at the starting positions of the robots



if __name__ == "__main__":
    grid = [[3,1,1],
            [2,5,1],
            [1,5,5],
            [2,1,1]]
    print(cherry_picking(grid))