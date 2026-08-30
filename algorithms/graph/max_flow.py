from collections import defaultdict

def max_flow(n_vertices, n_edges, source_index, sink_index, edges):

    adj_dict = defaultdict(lambda: defaultdict(list))
    flows = [0] * n_edges

    for source, sink, indicator in edges:
        adj_dict[source][sink].append(indicator)

    print(adj_dict)

    min_saturated = 0
    edge_visited = set()
    paths = []
    saturated_edges = set()

    def dfs (adj_dict: dict[dict[list]], node: int, prev_node: int, sink_index, path: tuple = (), solve = False):
        nonlocal min_saturated
        nonlocal edge_visited 
        nonlocal paths


        if node == sink_index: 
            if solve:
                min_saturated += 1 #every indipendent path to the sink node must have at least one saturated edge otherwise there are not guarantees that the path is required to reach the max flow, other path could absorbe the flow instead
                paths.append(path) 

                # each one of the edges of the indipendent path can be a saturated edge, choose always the first one, if an edge is already a saturated edge of anotehr indipendent path choose the second edge of the path and so on
                for i in range(len(path)-1):
                    if (path[i], path[i+1])  not in saturated_edges:
                        saturated_edges.add((path[i], path[i+1]))
                        break

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
    print(adj_dict)
    print(paths)
    print(saturated_edges)

    #reverse the graph
    reverse_adj_dict = defaultdict(lambda: defaultdict(list))

    for source, sink, indicator in edges:
        reverse_adj_dict[sink][source].append(indicator)

    print(reverse_adj_dict)

    edge_visited = set()

    dfs(reverse_adj_dict, sink_index, None, source_index)
    print(reverse_adj_dict)


    #compute the required flow for each edge by multiplying the required_flow at each edge of the provided graph and the inverted one
    result = []
    for source, sink, indicator in edges:
        edge_flow = adj_dict[source][sink][1] * reverse_adj_dict[sink][source][1] if indicator else 0
        edge_capacity = edge_flow if (source, sink) in saturated_edges else edge_flow + 1
        result.append((edge_flow, edge_capacity))

    print(result)

    return min_saturated


if __name__ == "__main__":
    n_vertices = 5
    n_edges = 6
    source_index = 1
    sink_index = 5
    edges = [[1, 2, 1], [2, 3, 1], [3, 5, 1], [1, 4, 1], [4, 3, 0], [4, 5, 1]]
    edges = [[1, 2, 1], [2, 3, 1], [3, 5, 1], [1, 4, 1], [4, 3, 1], [4, 5, 1]]
    print(max_flow(n_vertices, n_edges, source_index, sink_index, edges))