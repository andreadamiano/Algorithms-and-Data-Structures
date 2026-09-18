from collections import defaultdict
import bisect

cache = {}
stack = []

def find_blocks(adj_dict: dict[list[int]], blocks: list, visited = None, current_node = 1, parent_node = None, timer = 1, edge_visited: set = None): #if no parent is specified we root the spanning tree at node 1
    """
    A block is a sub-piece of a graph that has no single bottleneck inside it, meaning it takes at least 2 nodes deletions to breack a block, makig it a separate connected component.
    The algorithm uses dfs to construct the spannig tree of the graph, as it goes deeper the spanning tree it looks for backedges, which are edges forming a cycle with a node that 
    is higher in the spanning tree
    as it recurses it saves the encoutered edges into a stack to reconstruct the blocks present in the graph.
    As it goes down the tree it start a timer and for each node it save the time it encounters the node and the lower time it can jump up the tree, 
    as child are visited the lower timer is updated when a backedge is found to an already visited node as the min between the first encountered timer and the lower timer.
    During the descent the edges are saved onto a stack FIFO.
    As the recursive dfs backtrack each node update its own lower timer with the min between its lower timer and the child lowet timer, 
    to check if the parent node of the current node is a potential bottleneck we check if the lower timer of the current node is >= of the first encountered timer of the parent node, 
    if it is the node is a bottleneck node and to reconstruct the block all edges up untill the bottleneck node are removed from the stack.
    """

    if not visited:
        visited = set()

    if edge_visited is None:
        edge_visited = set()

    encountered = lower = timer
    cache[current_node] = (encountered, lower)
    visited.add(current_node)

    for neighbor in adj_dict[current_node]:
        if neighbor == parent_node:
            continue

        if (current_node, neighbor) in edge_visited:
            continue

        edge_visited.add((current_node, neighbor))
        edge_visited.add((neighbor, current_node))
        stack.append((current_node, neighbor)) #append the visited edge on the FIFO stack to pop them when a bottleneck node is found 

        if neighbor not in visited:

            child_encountered, child_lower = find_blocks(adj_dict, blocks, visited, neighbor, current_node, timer + 1, edge_visited)
            lower = min(child_lower, lower)

        elif parent_node: #if the node was already visited, it means there is a cycle, which means that the current node has a shortcut to a node that is higher on the spanning tree 
            child_encountered, child_lower = cache[neighbor]
            lower = min(child_encountered, lower)
            cache[current_node] = (encountered, lower)

    #check if the parent node is a bottleneck node 
    if parent_node:
        parent_encountered, parent_lower = cache[parent_node]

        if lower >= parent_encountered: #if the node didn't find any higher level nodes to hold on to, it means that the parent is the bottleneck node 
            current_block = []
            while True:
                edge = stack.pop()
                current_block.append(edge)

                if edge == (parent_node, current_node):
                    break

            blocks.append(current_block)

    cache[current_node] = (encountered, lower)
    return cache[current_node]
        

def check_block_planarity(adj_dict: dict[list[int]], parent_node: int = None, current_node: int = 1, spine: set= None, spine_index = 0, spine_node_dict: dict = None, left: list = None, right: list = None, back_edges: set = None):
    """
    The idea is to draw a block on a 2d plane withou line crossing.
    It starts by stretching all edges found by dfs vertically on a spine.
    Every non tree edge is a back-edge jumping back to an ancestor.
    Since the main dfs spine is a vertical line, every back-edge can only curve around eihter to the left or to the right side of the spine,
    if a back-edge collide we the already present back-edge both on the right and on teh left, the block is not coplanar.
    """
    if right is None:
        right = list()

    if left is None:
        left = list()

    if spine is None:
        spine = set()

    if spine_node_dict is None:
        spine_node_dict = dict()

    if back_edges is None:
        back_edges = set()

    spine_node_dict[current_node] = spine_index
    spine.add(current_node)

    for neighbor in adj_dict[current_node]:
        if neighbor == parent_node:
            continue

        if neighbor not in spine:
            if not check_block_planarity(adj_dict, current_node, neighbor, spine, spine_index +1, spine_node_dict, left, right, back_edges):
                return False

        elif ((current_node, neighbor) in back_edges):
            continue

        else:
            result = True

            #check for any overlapping window in left
            for source, dest in left:
                if (spine_node_dict[source] < spine_node_dict[current_node] and spine_node_dict[dest] < spine_node_dict[neighbor]) or (spine_node_dict[source] > spine_node_dict[current_node] and spine_node_dict[dest] > spine_node_dict[neighbor]):
                    result = False
                    break

            if result:
                left.append((current_node, neighbor))
                back_edges.add((current_node, neighbor))
                back_edges.add((neighbor, current_node))
            else:
                for source, dest in right:
                    if (spine_node_dict[source] < spine_node_dict[current_node] and spine_node_dict[dest] < spine_node_dict[neighbor]) or (spine_node_dict[source] > spine_node_dict[current_node] and spine_node_dict[dest] > spine_node_dict[neighbor]):
                        return False

                right.append((current_node, neighbor))
                back_edges.add((current_node, neighbor))
                back_edges.add((neighbor, current_node))
            
    return True


def check_planarity(edges: list[int]):
    """
    A graph is defined as planar if it can be drawned without crossing edges. For planar graphs it is valid the following Euler formula: V - E + F = 2, where
        - V: vertices
        - E: edges
        - F: faces
    this rule can be further generalized by the formula: E <= 3V - 6, in the case we don't know upfront the number of faces.
    If a graph is not satisying this rule, for sure it's not planar.
    """

    #build the adjecny dict 
    adj_dict = defaultdict(list)
    blocks = []
    n_edges = len(edges)
    vertices_set = set()

    for source, dest in edges:
        vertices_set.add(source)
        vertices_set.add(dest)
        adj_dict[source].append(dest)
        adj_dict[dest].append(source)

    n_vertices = len(vertices_set)

    if n_edges > 3 * n_vertices - 6:
        return False
        
    find_blocks(adj_dict, blocks)
    print(blocks)

    #build adj dict for every block found
    for block in blocks:
        adj_dict = defaultdict(list)
        for source, dest in block:
            adj_dict[source].append(dest)
            adj_dict[dest].append(source)

        if not check_block_planarity(adj_dict):
            return False


    return True

if __name__ == "__main__":
    # edges = [[1,2], [1,3],[2,3], [3,4]]
    edges = [[1,2], [1,3],[2,3], [3,4], [4,2]]
    # edges = [[1,2], [2,3],[3,4], [4,5], [5,1], [1,4], [1,3], [2,4], [2,5], [3,5]]
    print(check_planarity(edges))