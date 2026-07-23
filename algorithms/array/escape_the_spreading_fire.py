from collections import defaultdict, deque

def escape(grid: list[list]):
    rows = len(grid)
    cols = len(grid[0])

    man_times =  [[-1] * cols for _ in range(rows)]
    fire_times =  [[-1] * cols for _ in range(rows)]

    fire_positions = []

    #scan the grid in order to get the initial fire positions
    for row in range(rows):
        for col in range(cols):
            if grid[row][col] == 1:
                fire_positions.append((row, col))


    #the idea is to run first bfs to get both the fire time to spread to each cell
    #while at the same time to get the man times to get to the end of the grid, while saving the shortest path
    #once the bfs is finished traverse the shortest path back and compute the difference of the man time and the fire time on the shortest path
    #the max wait time will be the smallest difference

    def bfs(start_pos: list, time_matrix, track_path: bool = False):
        queue = deque()

        #populate queue
        for row, col in start_pos:
            time_matrix[row][col] = 0
            queue.append((row, col, 0)) 

        if track_path:
            path_parents = defaultdict(lambda: defaultdict(list))

        while queue:

            current_row, current_col, current_time = queue.popleft()

            for step in [[1,0], [0,1], [-1,0], [0,-1]]:
                next_row, next_col = current_row + step[0], current_col + step[1]
                if next_row < 0 or next_row >= rows or next_col < 0 or next_col >= cols or grid[next_row][next_col] == 2:
                    continue

                #if it's the first time encountering the node push to the queue
                if time_matrix[next_row][next_col] == -1:
                    time_matrix[next_row][next_col] = current_time + 1
                    queue.append((next_row, next_col, current_time + 1))

                    if track_path:
                        path_parents[next_row][next_col].append((current_row, current_col))

                #otherwise simply register the alternative shortest path
                elif track_path and time_matrix[next_row][next_col] == current_time + 1:
                    path_parents[next_row][next_col].append((current_row, current_col))


        return path_parents if track_path else None
        

    path_parents = bfs([(0,0)], man_times, track_path=True)
    bfs(fire_positions,  fire_times, track_path=False)

    # print(man_times)
    # print(fire_times)

    #if the man can't reach the end
    if man_times[-1][-1] == -1:
        return -1

    #if fire can't reach the end 
    if fire_times[-1][-1] == -1:
        return 1000000000

    #follow the shortest path backward while tracking the difference between the man time and the fire time
    current_positions = [(rows-1,cols-1)]
    min_diff = float("inf")

    while  (0,0) not in current_positions:
        max_diff = float("-inf")
        best_position = None

        for current_pos in current_positions:
            current_row, current_col = current_pos
            diff = fire_times[current_row][current_col] - man_times[current_row][current_col]

            if (current_row, current_col) != (rows-1,cols-1):
                diff -= 1

            best_position = current_pos if diff > max_diff else best_position
            max_diff = max(max_diff, diff)

            
        min_diff = min(min_diff, max_diff)
        current_positions = path_parents[best_position[0]][best_position[1]]

        # it means no solution to the end was found
        if not current_positions:
            return -1


    return min_diff if min_diff >= 0 else -1

if __name__ == "__main__":
    grid = [
        [0,2,0,0,0,0,0],
        [0,0,0,2,2,1,0],
        [0,2,0,0,1,2,0],
        [0,0,2,2,2,0,2],
        [0,0,0,0,0,0,0]
        ]

    # grid = [[0,0,0,0],[0,1,2,0],[0,2,0,0]]

    grid = [[0,0,0],[2,2,0],[1,2,0]]

    # grid = [[0,2,0,0,1],[0,2,0,2,2],[0,2,0,0,0],[0,0,2,2,0],[0,0,0,0,0]]

    # grid = [[0,2,1,1,0],[1,2,0,0,1],[2,2,1,1,0]]

    # grid = [[0,1,1],[2,0,1],[1,0,0],[2,2,0],[1,0,0]]

    # grid = [[0,2,0,0,1],[0,2,0,2,2],[0,2,0,0,0],[0,0,2,2,0],[0,0,0,0,0]]

    # grid = [[0,0,2,2,1,1,0,2,1,1,2,2,0,2,2,1,2,0,1,2,2,0,1,2,2,1,2,2],[2,2,2,1,1,2,2,1,2,0,1,1,1,2,2,1,1,0,2,2,2,0,1,0,1,2,2,2],[0,0,1,1,0,1,2,0,1,1,1,1,0,2,0,2,0,2,1,1,0,2,1,2,2,2,1,2],[2,2,0,0,0,0,1,0,1,0,2,0,1,0,2,0,0,1,2,1,0,1,1,1,2,0,2,0],[2,2,1,1,1,1,1,0,0,0,0,2,0,1,1,1,1,2,0,2,1,1,2,0,2,0,2,0],[0,1,0,1,2,2,2,0,2,0,2,2,1,2,0,0,1,0,2,0,2,0,1,2,2,0,2,0],[1,0,2,2,2,0,2,0,2,0,2,0,1,0,2,2,0,2,1,1,1,0,1,0,1,1,0,0],[0,1,2,0,1,0,1,0,2,1,2,0,1,1,1,1,0,1,1,0,0,2,0,1,0,1,0,2],[2,1,1,0,1,1,2,2,1,2,2,1,0,1,0,0,0,2,1,0,2,2,1,2,1,2,0,1],[1,1,2,0,2,2,1,2,0,2,1,1,0,0,0,2,2,2,2,1,2,2,0,2,1,1,2,0],[2,1,2,2,0,0,1,0,1,2,1,0,1,0,2,0,0,1,1,0,2,0,2,0,1,2,2,0],[1,0,1,1,0,0,0,0,0,1,0,2,0,2,1,2,1,1,0,1,0,0,2,1,2,1,0,2],[2,0,1,0,2,0,1,0,2,0,2,1,2,0,2,2,2,1,0,2,1,0,1,2,1,0,1,1],[0,2,2,1,0,2,1,0,1,2,2,1,2,2,1,2,0,1,2,2,0,2,1,0,2,1,0,0],[0,2,2,2,1,2,1,0,0,2,2,0,1,0,2,1,0,0,2,1,1,1,2,1,2,1,0,1],[2,2,2,1,1,1,1,0,2,2,2,1,0,0,2,2,0,0,1,1,0,0,2,1,2,1,2,2],[2,1,2,1,1,1,0,2,1,0,1,1,2,1,0,0,1,1,2,1,2,2,1,2,0,2,0,0]]

    # grid = [[0,0,0,0,0],[0,2,0,2,0],[0,2,0,2,0],[0,2,1,2,0],[0,2,2,2,0],[0,0,0,0,0]]

    grid = [[0,0,0,0,0,0],[0,2,2,2,2,0],[0,0,0,1,2,0],[0,2,2,2,2,0],[0,0,0,0,0,0]]
    
    print(escape(grid))