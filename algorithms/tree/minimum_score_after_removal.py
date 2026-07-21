from collections import defaultdict


def min_score(nums, edges):
    """Brute force solition with precomputing the XOR incremental XOR list"""
    n = len(edges)

    #compute adjency list 
    adj_list = defaultdict(list)
    for source, destination in edges:
        adj_list[source].append(destination)
        adj_list[destination].append(source)


    #precompute XOR incrementally via a single dfs pass 
    #during dfs we will register the time of entering and the time of exting the nodes, to identify later if a node is an ancestor of another node using those times
    xor_list = [0] * (n + 1)
    visited = [False] * (n + 1)
    timer = 0
    tin = [0] * (n+1)
    tout = [0] * (n+1)

    def dfs(node):
        nonlocal timer 

        visited[node] = True
        xor_list[node] = nums[node]
        tin[node] = timer
        timer += 1
        for desc in adj_list[node]:
            if not visited[desc]:
                xor_list[node] ^= dfs(desc)

        tout[node] = timer
        timer += 1
        return xor_list[node]

    #choose arbitrarly the root node
    root_node = 0
    dfs(root_node)

    def is_ancestor(node1, node2):
        """Returns true if node1 is the ancestor of node2"""
        return tin[node1] <= tin[node2] and tout[node1] >= tout[node2]


    #test every combination of 2 edges 
    min_score = float("inf")
    for i in range(n):
        if i == root_node: #root node is already a rooted node, it can be skipped
            continue

        for j in range(i+1, n):
            #every time and edge is cut, the tree will be split in 2 connected componets
            #before computing the XOR of the 2 connected components the parent and the descendant must be identified
            #the XOR value of the parent is XOR[parent] ^= XOR[child]
            #instead of thinking in terms of edges, we will think in terms of rooted nodes, we will split the tree into 3 subtree with 3 rooted nodes 
            #there are 2 possile cases, either one of the 2 nodes is the ancestor of the other, or the 2 nodes are on separate branches

            if is_ancestor(i, j):
                comp1 = xor_list[j]
                comp2 = xor_list[j] ^ xor_list[i]
                comp3 = xor_list[root_node] ^ xor_list[i] 

            elif is_ancestor(j,i):
                comp1 = xor_list[i]
                comp2 = xor_list[j] ^ xor_list[i]
                comp3 =  xor_list[root_node] ^ xor_list[j] 

            else:
                comp1 = xor_list[i]
                comp2 = xor_list[j]
                comp3 = xor_list[root_node] ^ xor_list[i] ^ xor_list[j]

            score = max(comp1, comp2, comp3) - min(comp1, comp2, comp3)
            min_score = min(min_score, score)


    return min_score    
     


if __name__ == "__main__":
    nums = [1,5,5,4,11]
    edges = [[0,1], [1,2], [1,3],[3,4]]
    print(min_score(nums, edges))