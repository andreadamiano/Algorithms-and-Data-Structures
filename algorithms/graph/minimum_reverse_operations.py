from sortedcontainers import SortedList
from collections import deque

def min_reverse_opeartions(n, p, banned, k):
    solution = [-1] * n
    solution[0] = 0

    lists = [SortedList(), SortedList()] 

    for i in range(n):
        if i != p and i not in banned:
            lists[i%2].add(i)

    # bfs 
    q = deque()
    q.append(p)


    while(q):
        current_node = q.popleft()

        #find left most index where the subarray should start 
        start_left = max(0, current_node-k+1)
        start_right = min(current_node, n - k)

        if start_right < start_left:
            continue

        #find reachable nodes 


    return lists


if __name__ == "__main__":
    n = 4
    p = 0 
    banned = [1,2]
    k = 4
    print(min_reverse_opeartions(n, p, banned, k))