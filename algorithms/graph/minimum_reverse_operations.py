from sortedcontainers import SortedList
from collections import deque
import bisect 

def min_reverse_opeartions(n, p, banned, k):
    """This solution gets TLE in leetcode"""
    def rotate(curr_node, start, k):
        return start + (k - 1) + (start - curr_node)


    solution = [-1] * n
    solution[p] = 0

    # bfs 
    q = deque()
    q.append(p)


    while(q):
        current_node = q.popleft()

        if current_node == n:
            return

        #find left most index where the subarray should start 
        start_left = max(0, current_node-k+1)
        start_right = min(current_node, n - k)

        if start_right < start_left:
            continue

        #find reachable nodes 
        for start in range(start_left, start_right+1):
            neighbor_node = rotate(current_node, start, n, k)

            if neighbor_node not in banned and neighbor_node != current_node and solution[neighbor_node] == -1:
                solution[neighbor_node] = solution[current_node] + 1
                q.append(neighbor_node)

    return solution


def  min_reverse_opeartions(n, p, banned, k):
    """
    In order to avoid TLE this improvements are used:
    - store in a set all unvisited node
    - separate the univited set into odd and even sets, since depending on the current node and the size of the window we can now for certain on which of the 2 the neighbors of a node will be 
    - use binary search to find the first neighbor in the unvisited set (since we know that all neighbor nodes will be in a range from min_neighbor:max_neighbor)
    """
    def rotate(curr_node, start, k):
        return start + (k - 1) + (start - curr_node)

    solution = [-1] * n
    solution[p] = 0

    unvisited = [SortedList(), SortedList()]

    #populate both sets
    banned_set = set(banned)
    for i in range(n):
        if i not in banned_set and i != p:
            unvisited[i & 1].add(i)

    #initialize queue
    queue = deque()
    queue.append(p)

    while queue:
        current_node = queue.popleft()

        if current_node == n:
            return solution

        min_start = max(0, current_node - k + 1)
        max_start = min(current_node, n - k)

        min_neighbor = rotate(current_node, min_start, k)
        max_neighbor = rotate(current_node, max_start, k)

        #get the parity of the neighbors
        parity = (current_node + k - 1) & 1
        unvisited_neighbors: SortedList = unvisited[parity]

        #find the first unvisited neighbor in the min:max range identified
        index = unvisited_neighbors.bisect_left(min_neighbor)

        node_to_remove = [] #never remove in place while iterating on it 
        while index < len(unvisited_neighbors) and unvisited_neighbors[index] <= max_neighbor:
            queue.append(unvisited_neighbors[index])
            solution[unvisited_neighbors[index]] = solution[current_node] + 1
            node_to_remove.append(unvisited_neighbors[index])
            index += 1            

        for node in node_to_remove:
            unvisited_neighbors.remove(node)

    return solution


if __name__ == "__main__":
    # n = 4
    # p = 0 
    # banned = [1,2]
    # k = 4

    n = 5
    p = 0
    banned = []
    k = 2
    print(min_reverse_opeartions(n, p, banned, k))