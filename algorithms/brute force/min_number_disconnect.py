def min_disconnect(grid: list[list]):
    rows = len(grid)
    cols = len(grid[0])

    def dfs(r, c, visited: set):
        if r < 0 or r == rows or c < 0 or c == cols or not grid[r][c] or (r, c) in visited:
            return 
        
        visited.add((r, c))
        neighbors = [[r+1,c], [r-1,c], [r,c+1], [r,c-1]]
        for nieghbor in neighbors:
            dfs(nieghbor[0], nieghbor[1], visited)

    def count_islands():
        visited = set()
        islands = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] and (r, c) not in visited:
                    dfs(r, c, visited)
                    islands += 1

        return islands
    
    islands = count_islands()

    if islands > 1 or islands == 0:
        return 0
    
    #try to delete one cell at a time
    visited = set()
    for r in range(rows):
            for c in range(cols):
                if grid[r][c] and (r, c) not in visited:
                    grid[r][c] = 0
                    islands = count_islands()
                    if islands > 1 or islands == 0:
                        return 1
                    grid[r][c] = 1

    return 2





if __name__ == "__main__":
    grid = [
        [0,1,1,0],
        [0,1,1,0],
        [0,0,0,0]
    ]
    grid = [
        [0,0,0],
        [0,1,0],
        [0,0,0]]
    print(min_disconnect(grid))