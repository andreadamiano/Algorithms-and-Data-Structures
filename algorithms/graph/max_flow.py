from collections import defaultdict, deque

def min_saturated(adj_dict: dict[dict[list]], source_node: int, sink_node: int):
    """
    Ford-Fulkerson algorithm to compute the max flow, it repetedly compute a path from the source to the sink
    if a path is found decrement the forward capacity and increment the backward capacity,
    repeat untill no more path are found, 
    at the end of the algorithm the reachable nodes are part of the source split
    the value of the split (sum of the forward flows edges form the source split to the sink split) is equal to the max flow
    """

    def bfs(node):
        visited = set()
        queue = deque()
        queue.append(((node, ), float("inf")))

        while queue:
            current_path, min_capacity = queue.popleft()
            visited.add(current_path[-1])

            if current_path[-1] == sink_node:
                return True, current_path, min_capacity

            for neighbor, capacity in adj_dict[current_path[-1]].items():
                if  capacity and neighbor not in visited:
                    queue.appendleft((current_path + (neighbor, ), min(min_capacity, adj_dict[current_path[-1]][neighbor])))

        return False, current_path, min_capacity

    result, path, min_capacity = bfs(source_node)
    while result :

        for i in range(len(path)-1):
            source = path[i]
            sink = path[i+1]
            adj_dict[source][sink] -= min_capacity
            adj_dict[sink][source] += min_capacity

        result, path, min_capacity = bfs(source_node)

    # at the end path will hold the source split 
    edges = set()
    path_set = set(path)
    for source in path:
        for sink in adj_dict[source].keys():
            if sink not in path_set:
                edges.add((source, sink))

    return edges


def max_flow(n_vertices, n_edges, source_index, sink_index, edges):
    adj_dict = defaultdict(lambda: defaultdict(list))
    edge_visited = set()
    paths = []

    for source, sink, indicator in edges:
        adj_dict[source][sink].append(indicator)

    def dfs (adj_dict: dict[dict[list]], node: int, prev_node: int, sink_index, path: tuple = (), solve = False):
        nonlocal edge_visited 
        nonlocal paths

        if node == sink_index: 
            if solve:
                paths.append(path) #save every path to the sink node 

            if (prev_node, node) not in edge_visited:
                edge_visited.add((prev_node, node))
                adj_dict[prev_node][node].append(1)

            return 1

        required_flow = 0
        for neighbor, attributes in adj_dict[node].items():
            if attributes[0]:
                required_flow += dfs(adj_dict, neighbor, node, sink_index, path + (neighbor,), solve)

        if prev_node and (prev_node, node) not in edge_visited:
            edge_visited.add((prev_node, node))
            adj_dict[prev_node][node].append(required_flow)

        return required_flow


    dfs(adj_dict, source_index, None, sink_index, (source_index, ), True) 

    if not paths:
        return -1, paths
    
    print(adj_dict)
    print(paths)
    # print(saturated_edges)

    #reverse the graph
    reverse_adj_dict = defaultdict(lambda: defaultdict(list))

    for source, sink, indicator in edges:
        reverse_adj_dict[sink][source].append(indicator)

    edge_visited = set()
    dfs(reverse_adj_dict, sink_index, None, source_index)
    # print(reverse_adj_dict)


    #compute the required flow for each edge by multiplying the required_flow at each edge of the provided graph and the inverted one
    residual_adj_dict = defaultdict(lambda : defaultdict(int))
    for path in paths:
        for i in range(len(path)-1):
            source = path[i]
            sink = path[i+1]
            edge_flow = adj_dict[source][sink][1] * reverse_adj_dict[sink][source][1] 
            residual_adj_dict[source][sink] =  edge_flow
            residual_adj_dict[sink][source] = 0
            # edge_capacity = edge_flow if (source, sink) in saturated_edges else edge_flow + 1
            # result.append((edge_flow, edge_capacity))

    print(residual_adj_dict)

    saturated_edges = min_saturated(residual_adj_dict, source_index, sink_index)
    print(saturated_edges)

    result = []
    for source, sink, _ in edges:
        edge_flow = residual_adj_dict[source][sink] + residual_adj_dict[sink][source]
        edge_capacity = edge_flow if (source, sink) in saturated_edges else edge_flow + 1
        result.append((edge_flow, edge_capacity))

    return len(saturated_edges), result

if __name__ == "__main__":
    # n_vertices = 5
    # n_edges = 6
    # source_index = 1
    # sink_index = 5
    # edges = [[1, 2, 1], [2, 3, 1], [3, 5, 1], [1, 4, 1], [4, 3, 0], [4, 5, 1]]
    # edges = [[1, 2, 1], [2, 3, 1], [3, 5, 1], [1, 4, 1], [4, 3, 1], [4, 5, 1]]

    edges = [[45, 14, 0], [36, 37, 0], [23, 11, 0], [33, 47, 0], [9, 12, 0], [10, 20, 1], [21, 4, 1], [4, 22, 0], [22, 45, 0], [7, 22, 0], [29, 40, 0], [2, 3, 0], [43, 23, 0], [48, 31, 0], [35, 40, 0], [29, 37, 0], [20, 50, 1], [44, 21, 0], [36, 6, 0], [38, 41, 0], [10, 17, 0], [44, 38, 0], [4, 15, 1], [15, 44, 1], [44, 40, 1], [6, 4, 0], [10, 6, 1], [46, 35, 0], [23, 13, 0], [4, 14, 0], [46, 12, 0], [8, 23, 0], [33, 48, 0], [22, 11, 0], [28, 27, 0], [34, 42, 0], [17, 49, 0], [26, 36, 1], [22, 21, 0], [17, 5, 0], [43, 3, 0], [48, 4, 0], [35, 9, 0], [44, 8, 0], [13, 17, 0], [17, 6, 0], [32, 34, 0], [30, 50, 0], [43, 16, 0], [15, 12, 0], [12, 42, 0], [42, 49, 0], [16, 43, 0], [19, 16, 0], [19, 13, 0], [1, 10, 1], [37, 50, 0], [47, 42, 0], [4, 25, 0], [18, 14, 0], [32, 26, 0], [39, 42, 0], [13, 44, 0], [32, 29, 0], [20, 3, 0], [24, 37, 0], [31, 12, 0], [22, 28, 0], [47, 15, 0], [36, 50, 1], [47, 41, 0], [6, 44, 1], [44, 35, 0], [25, 6, 0], [24, 11, 0], [35, 43, 0], [40, 18, 0], [19, 17, 0], [3, 21, 0], [13, 7, 0], [25, 35, 0], [22, 9, 0], [20, 38, 0], [44, 39, 0], [33, 8, 0], [34, 36, 0], [18, 41, 0], [25, 42, 0], [2, 4, 0], [1, 22, 0], [12, 3, 0], [23, 42, 0], [26, 44, 0], [17, 21, 0], [1, 21, 1], [34, 29, 0], [40, 26, 1], [33, 12, 0], [21, 8, 0], [7, 18, 0]]
    first_line = "50 100 1 50".split()
    

    # first_line = input().split()
    n_vertices = int(first_line[0])
    n_edges = int(first_line[1])
    source_index = int(first_line[2])
    sink_index = int(first_line[3])

    # edges = []
    # for i in range(n_edges):
    #     edge = [int(x) for x in input().split()]
    #     edges.append(edge)

    min_saturated, result = max_flow(n_vertices, n_edges, source_index, sink_index, edges)
    # print(min_saturated)
    # for edge_flow, edge_capacity in result:
    #     print(f"{edge_flow} {edge_capacity}")