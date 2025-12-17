# from itertools import combinations

def notIn(node, subset):
    """
    This function check if the node is part of the bit map
    """
    return ((subset >> node) & 1) == 0

# def combination(iterable, k):
    # for subset in combinations(iterable, k):
    #     bitmask = 0
    #     for node in subset:
    #         bitmask  |= (1 << node)
    #     yield bitmask

def combination(N, k):
    """
    combination N choose k
    """
    subsets = []
    combinations(0, 0, N, k, subsets)
    return subsets

def combinations(set, at, N, k, subsets: list):
    if k ==0:
        subsets.append(set)

    for i in range(at, N):
        set |= (1 << i)
        combinations(set, i+1, N, k-1, subsets)
        #backtracking
        set ^= (1 << i)

def setup(graph, memo, S, N):
    """
    Initialize the memo table storing the optimal solution from the start node to every other node
    The dp table store: memo[visited_set][last_node]
    since the cost to reach a set of nodes depends both on the order and on the visited nodes
    the base case is the cost of reaching the nodes directly accessible from S
    """
    for i in range(N):
        # if i == S:
        #     continue
        #set the subpath of the starting node and the next node to the weight of the edge
        memo[(1 << S) | (1 << i)][i] = graph[S][i]

def solve(graph, memo, S, N):
    #this first loop represent the number of nodes in a partial tour
    #loop over all partial tours starting from a tour of 3 nodes (since 2 nodes have been already initialized)
    for r in range(3, N+1):
        #N choose r combination without repetition
        #this generate all possible partial tours of lenght r starting from node S
        # for subset in combination(range(N), r):
        #generate all possible tour of 3 nodes 
        for subset in combination(N, r):
            #S must be part of the generated tour 
            if notIn(S, subset):
                continue  

            #loop over all possible nodes to find a possible next node,
            #which is found if it's not the starting node, but if it's part of the current subset
            #so for each subset find a possible next node
            for next in range(N):
                if next == S or notIn(next, subset):
                    continue
                #this is the subset without the next node,
                #to look up in the memo table the optimal cost to reach next
                #take the tour without the next node 
                state = subset ^ (1 << next)

                minDistance = float("inf")
                #endnode represent the last node before reaching the next node
                #so in this algorithm we "brute force" over all possible previous node with all possibel next node
                for endNode in range(N):
                    if endNode == S  or notIn(endNode, state) :
                        continue
                    newDistance = memo[state][endNode] + graph[endNode][next]

                    if newDistance < minDistance:
                        minDistance = newDistance

                #save the result in the memo table
                memo[subset][next] = minDistance


def findMinCost(graph, memo, S, N):
    #bitmask with all bits sets to 1 , which represent the final state
    #containing the optimum cost to visit each nodes until the semi last node,
    #before going back to the last
    end_state = (1 << N) -1
    minTourCost = float("inf")

    #test each possible node before the end, which is also the start
    for endNode in range(N):
        if endNode == S:
            continue

        #compute the cost to go back to the starting node
        tourCost = memo[end_state][endNode]  + graph[endNode][S]
        if tourCost < minTourCost:
            minTourCost = tourCost

    return minTourCost

def findOptimalTour(graph, memo, S, N):
    #start backtracking from the starting node
    lastIndex = S
    state = (1 << N) -1  #end state where all nodes have been visited
    tour = [0] * (N+1) #initialize a list containing the tour

    #find which node should be at position i in the tour
    for i in range(N-1, 0, -1):
        #the index keeps track of the best candidate node for this position of the route
        minDist = float("inf")
        minNode = -1
        #loop over all possible nodes remaining
        for j in range(N):
            if j == S or notIn(j, state):
                continue
            newDist = memo[state][j] + graph[j][lastIndex]
            if newDist < minDist:
                minDist = newDist
                minNode = j
        tour[i] = minNode

        #remove minNode from the visited nodes
        state = state ^ (1 << minNode)
        lastIndex = minNode

    tour[0] = tour[N] = S #the first and last nodes of the route are the starting node
    return tour


def TSP(graph, start):
    N = len(graph)

    memo = [[float('inf')] * N for _ in range(1 << N)] #2d DP table of size [2^N][N]

    setup(graph, memo, S, N)
    solve(graph, memo, S, N)
    print(f"Memo table: {memo}")
    minCost = findMinCost(graph, memo, S, N)
    print(f"MinCosst: {minCost}")
    tour = findOptimalTour(graph, memo, S, N)
    print(f"Tour: {tour}")

    return (minCost, tour)



if __name__ == "__main__":
    #adjacency matrix for TSP (4 cities)
    # 0 means no self-loop, and a large number (e.g., float('inf')) means no direct path
    graph = [
        [0, 10, 15, 20],
        [10, 0, 35, 25],
        [15, 35, 0, 30],
        [20, 25, 30, 0]
    ]


    S = 0  # starting node
    TSP(graph, S)

