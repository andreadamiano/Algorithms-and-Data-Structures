def notIn(node, subset):
    """
    This function check if the node is part of the bit map
    """
    return ((subset >> node) & 1) == 0

def combination(N, k):
    """
    combination N choose k without repetition
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
        set ^= (1 << i) #backtracking

def setup(graph, dp, S, N):
    """
    Initialize the dp table storing the optimal solution from the start node to every other node
    The dp table store: dp[visited_set][last_node]
    since the cost to reach a set of nodes depends both on the order and on the visited nodes
    the base case is the cost of reaching the nodes directly accessible from S
    """
    for i in range(N):

        #asign to the subset of the starting node and the next node the weight of the edge connecting them 
        dp[(1 << S) | (1 << i)][i] = graph[S][i]

def solve(graph, dp, S, N):
    #this first loop represent the number of nodes in a partial tour
    #loop over all partial tours starting from a tour of 3 nodes (since 2 nodes have been already initialized)
    for tour_len in range(3, N+1):
        #N choose r combination without repetition
        #this generate all possible partial tours of lenght r starting from node S
        for tour_set in combination(N, tour_len):
            #S must be part of the generated tour 
            if notIn(S, tour_set):
                continue  

            #loop over all possible nodes to find a possible next node,
            #which is found if it's not the starting node, but if it's part of the current subset
            #so for each subset find a possible next node
            for nextNode in range(N):
                if nextNode == S or notIn(nextNode, tour_set):
                    continue
                #this is the subset without the next node,
                #to look up in the dp table the optimal cost to reach next
                #take the tour without the next node 
                prev_tour_set = tour_set ^ (1 << nextNode)

                minDistance = float("inf")
                #endnode represent the last node before reaching the next node
                #so in this algorithm we "brute force" over all possible previous node with all possibel next node
                for prevNode in range(N):
                    if prevNode == S  or notIn(prevNode, prev_tour_set):
                        continue

                    minDistance = min(dp[prev_tour_set][prevNode] + graph[prevNode][nextNode], minDistance)

                #save the result in the dp table
                dp[tour_set][nextNode] = minDistance


def findMinCost(graph, dp, S, N):
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
        tourCost = dp[end_state][endNode]  + graph[endNode][S]
        if tourCost < minTourCost:
            minTourCost = tourCost

    return minTourCost

def findOptimalTour(graph, dp, S, N):
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
            newDist = dp[state][j] + graph[j][lastIndex]
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

    dp = [[float('inf')] * N for _ in range(1 << N)] #2d DP table of size [2^N][N]

    setup(graph, dp, S, N)
    solve(graph, dp, S, N)
    print(f"dp table: {dp}")
    minCost = findMinCost(graph, dp, S, N)
    print(f"MinCosst: {minCost}")
    tour = findOptimalTour(graph, dp, S, N)
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

