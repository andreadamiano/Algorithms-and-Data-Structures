from collections import defaultdict, deque

MAX_TIME = 10**9

def escape(grid: list[list]):

    def bfs(start_pos: list, time_matrix, rows, cols, track_path: bool = False):
        queue = deque()
        visited = set()

        #populate queue
        for row, col in start_pos:
            time_matrix[row][col] = 0
            queue.append((row, col, 0)) 
            visited.add((row, col))

        if track_path:
            path_parents = defaultdict(lambda: defaultdict(list))

        while queue:
            current_row, current_col, current_time = queue.popleft()
            visited.add((current_row, current_col))

            for step in [[1,0], [0,1], [-1,0], [0,-1]]:
                next_row, next_col = current_row + step[0], current_col + step[1]

                if (next_row, next_col) in visited:
                    continue
                
                if next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols or grid[next_row][next_col] == 2:
                    continue

                #if it's the first time encountering the node push to the queue
                if time_matrix[next_row][next_col] == -1:
                    time_matrix[next_row][next_col] = current_time + 1
                    queue.append((next_row, next_col, current_time + 1))

                #register parent node
                if track_path:
                    path_parents[next_row][next_col].append((current_row, current_col))

        return path_parents if track_path else None

    rows = len(grid)
    cols = len(grid[0])

    man_times =  [[-1] * cols for _ in range(rows)] #save the min time for the man to reach each cell
    fire_times =  [[-1] * cols for _ in range(rows)] #save the min time for the fire to reach each cell56
    fire_positions = []

    #scan the grid in order to get the initial fire positions
    for row in range(rows):
        for col in range(cols):
            if grid[row][col] == 1:
                fire_positions.append((row, col))


    #the idea is to run bfs a first time to get the fire time to spread to each cell
    #and a second time to get the man times to get to the end of the grid, while computing the shortest path to the end
    bfs(fire_positions,  fire_times, rows, cols, track_path=False)
    path_parents = bfs([(0,0)], man_times, rows, cols, track_path=True)

    #if the man can't reach the end
    if man_times[-1][-1] == -1:
        return -1

    #if fire can't reach the end 
    if fire_times[-1][-1] == -1:
        return MAX_TIME

    #follow the shortest path backward while tracking the difference between the man time and the fire time
    parent_positions = [(rows-1,cols-1)]
    min_diff = float("inf")

    while  (0,0) not in parent_positions:
        max_diff = float("-inf")
        best_position = None

        for parent in parent_positions:
            parent_row, parent_col = parent
            diff = fire_times[parent_row][parent_col] - man_times[parent_row][parent_col]

            if (parent_row, parent_col) != (rows-1,cols-1):
                diff -= 1

            best_position = parent if diff > max_diff else best_position
            max_diff = max(max_diff, diff)

        #prune early
        if max_diff < 0:
            return -1
            
        min_diff = min(min_diff, max_diff) #save the min diff, that will be the max time the man can wait before start escaping
        parent_positions = path_parents[best_position[0]][best_position[1]]

        # it means no solution to the end was found
        if not parent_positions:
            return -1


    return min_diff 

if __name__ == "__main__":
    grid = [
        [0,2,0,0,0,0,0],
        [0,0,0,2,2,1,0],
        [0,2,0,0,1,2,0],
        [0,0,2,2,2,0,2],
        [0,0,0,0,0,0,0]
        ]

    # grid = [[0,0,0,0],[0,1,2,0],[0,2,0,0]]

    # grid = [[0,0,0],[2,2,0],[1,2,0]]

    # grid = [[0,2,0,0,1],[0,2,0,2,2],[0,2,0,0,0],[0,0,2,2,0],[0,0,0,0,0]]

    # grid = [[0,2,1,1,0],[1,2,0,0,1],[2,2,1,1,0]]

    # grid = [[0,1,1],[2,0,1],[1,0,0],[2,2,0],[1,0,0]]

    # grid = [[0,2,0,0,1],[0,2,0,2,2],[0,2,0,0,0],[0,0,2,2,0],[0,0,0,0,0]]

    # grid = [[0,0,2,2,1,1,0,2,1,1,2,2,0,2,2,1,2,0,1,2,2,0,1,2,2,1,2,2],[2,2,2,1,1,2,2,1,2,0,1,1,1,2,2,1,1,0,2,2,2,0,1,0,1,2,2,2],[0,0,1,1,0,1,2,0,1,1,1,1,0,2,0,2,0,2,1,1,0,2,1,2,2,2,1,2],[2,2,0,0,0,0,1,0,1,0,2,0,1,0,2,0,0,1,2,1,0,1,1,1,2,0,2,0],[2,2,1,1,1,1,1,0,0,0,0,2,0,1,1,1,1,2,0,2,1,1,2,0,2,0,2,0],[0,1,0,1,2,2,2,0,2,0,2,2,1,2,0,0,1,0,2,0,2,0,1,2,2,0,2,0],[1,0,2,2,2,0,2,0,2,0,2,0,1,0,2,2,0,2,1,1,1,0,1,0,1,1,0,0],[0,1,2,0,1,0,1,0,2,1,2,0,1,1,1,1,0,1,1,0,0,2,0,1,0,1,0,2],[2,1,1,0,1,1,2,2,1,2,2,1,0,1,0,0,0,2,1,0,2,2,1,2,1,2,0,1],[1,1,2,0,2,2,1,2,0,2,1,1,0,0,0,2,2,2,2,1,2,2,0,2,1,1,2,0],[2,1,2,2,0,0,1,0,1,2,1,0,1,0,2,0,0,1,1,0,2,0,2,0,1,2,2,0],[1,0,1,1,0,0,0,0,0,1,0,2,0,2,1,2,1,1,0,1,0,0,2,1,2,1,0,2],[2,0,1,0,2,0,1,0,2,0,2,1,2,0,2,2,2,1,0,2,1,0,1,2,1,0,1,1],[0,2,2,1,0,2,1,0,1,2,2,1,2,2,1,2,0,1,2,2,0,2,1,0,2,1,0,0],[0,2,2,2,1,2,1,0,0,2,2,0,1,0,2,1,0,0,2,1,1,1,2,1,2,1,0,1],[2,2,2,1,1,1,1,0,2,2,2,1,0,0,2,2,0,0,1,1,0,0,2,1,2,1,2,2],[2,1,2,1,1,1,0,2,1,0,1,1,2,1,0,0,1,1,2,1,2,2,1,2,0,2,0,0]]

    # grid = [[0,0,0,0,0],[0,2,0,2,0],[0,2,0,2,0],[0,2,1,2,0],[0,2,2,2,0],[0,0,0,0,0]]

    # grid = [[0,0,0,0,0,0],[0,2,2,2,2,0],[0,0,0,1,2,0],[0,2,2,2,2,0],[0,0,0,0,0,0]]

    gris = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
    
    print(escape(grid))