from collections import defaultdict

def largest__color(colors, edges):
    n = len(colors)
    nodes_state = [0] * n #save a global state for each node: 0 - not visited, 1 - visiting, 2 - visited
    edge_list = defaultdict(list)

    for source, destination in edges:
        edge_list[source].append(destination)
    
    cache = {} #store the dictionary of color visited (it's important to store the whole dictionary and not just the max color, sicnce it will be used by upstream node to find the current max color)
    def dfs(curr_node):
        if nodes_state[curr_node] == 1: #cycle detected
            return None
        
        if curr_node in cache:
            return cache[curr_node]
        
        nodes_state[curr_node] = 1 #mark that we are currently visiting this node
        max_color_visited = defaultdict(int) #this dictionary will store the frequency of the color visited from the current node downstream

        for neighbor in edge_list[curr_node]:
            color_visited = dfs(neighbor)

            if not color_visited:
                return None #propagate the prune upwards
            
            #merge downstream color visited in order to get the max color of each path (so that upstream nodes can update the dictionary finding their path with the most frequent color)
            for color, frequency in color_visited.items():
                max_color_visited[color] = max(max_color_visited[color], frequency)

        max_color_visited[colors[curr_node]] += 1 #take into account the color of the current node
        nodes_state[curr_node] = 2 #mark the current node as visited
        cache[curr_node] = max_color_visited #cache the result
        return max_color_visited


    max_color_visited = 0
    for node in range(n):
        color_visited: dict = dfs(node)

        if not color_visited:
            return -1
        else:
            max_color_visited = max(max(color_visited.values()), max_color_visited)

    return max_color_visited



if __name__ == "__main__":
    colors = "abaca"
    edges = [[0,1], [0,2], [2,3], [3,4]]

    colors = "a"
    edges = [[0,0]]
    print(largest__color(colors, edges))