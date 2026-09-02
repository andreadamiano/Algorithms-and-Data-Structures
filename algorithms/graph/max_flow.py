from collections import defaultdict, deque
import copy

def bfs(adj_dict: dict[dict[int]], node: int, sink_node: int):
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
                    queue.append((current_path + (neighbor, ), min(min_capacity, adj_dict[current_path[-1]][neighbor])))

        return False, current_path, min_capacity


def min_saturated(adj_dict: dict[dict[int]], source_node: int, sink_node: int):
    """
    Ford-Fulkerson algorithm to compute the max flow, it repetedly compute a path from the source to the sink
    if a path is found decrement the forward capacity and increment the backward capacity,
    repeat untill no more path are found, 
    at the end of the algorithm the reachable nodes are part of the source split
    the value of the split (sum of the forward flows edges form the source split to the sink split) is equal to the max flow

    the problem requires to compute the cut with minimum edges (to be saturated), therefore a graph with all unit edges will be used, since: max flow = min cut = n edges * 1
    """
    residual_adj_dict = copy.deepcopy(adj_dict) #create a local copy
    result, path, min_capacity = bfs(residual_adj_dict, source_node, sink_node)
    while result :

        for i in range(len(path)-1):
            source = path[i]
            sink = path[i+1]
            residual_adj_dict[source][sink] -= min_capacity
            residual_adj_dict[sink][source] += min_capacity

        result, path, min_capacity = bfs(residual_adj_dict, source_node, sink_node)

    # at the end path will hold the source split 
    edges = set()
    path_set = set(path)
    for source in path:
        for sink in adj_dict[source].keys():
            if sink not in path_set and adj_dict[source][sink]:
                edges.add((source, sink))

    return edges


def compute_flows(adj_dict: dict[dict[int]], vertices: list, source_node: int, sink_node: int):
    adj_dict = copy.deepcopy(adj_dict) #create a local copy
    stop = False

    while not stop:
        stop = True
        for vertex in range(1, len(vertices)):
            flows = vertices[vertex]
            path = []
            direction = None
            if vertex == source_node or vertex == sink_node or flows[0] == flows[1]:
                continue

            #inflow > outflow
            elif flows[0] > flows[1]:
                _, path, _ = bfs(adj_dict, vertex, sink_node)
                stop = False

            #outflow > inflow
            else:
                _, path, _ = bfs(adj_dict, source_node, vertex)
                stop = False

            if path:
                diff = abs(flows[0] - flows[1])
                for i in range(len(path)-1):
                    source = path[i]
                    sink = path[i + 1]
                    adj_dict[source][sink] += diff

                    #update also vertices
                    vertices[source][1] += diff #outflow of source
                    vertices[sink][0] += diff #inflow of sink


    return adj_dict



def max_flow(n_vertices, n_edges, source_node, sink_node, edges):
    adj_dict = defaultdict(dict)
    residual_adj_dict = defaultdict(dict)
    vertices = [[0] * 2 for _ in range(n_vertices+1)]

    for source, sink, indicator in edges:
        adj_dict[source][sink] = indicator
        residual_adj_dict[source][sink] = indicator
        residual_adj_dict[sink][source] = indicator #add the reverse edge to traverse the graph backward 

        #precompute inflow and outflow
        if indicator:
            vertices[sink][0] += 1
            vertices[source][1] += 1

    print(adj_dict)
    print(vertices)
    adj_dict_flows = compute_flows(adj_dict, vertices, source_node, sink_node)

    print(adj_dict)
    print(vertices)

    saturated_edges = min_saturated(residual_adj_dict, source_index, sink_index)
    # print(saturated_edges)

    result = []
    for source, sink, _ in edges:
        edge_flow = adj_dict_flows[source][sink]
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
    print(min_saturated)
    for edge_flow, edge_capacity in result:
        print(f"{edge_flow} {edge_capacity}")