import heapq

def maximize_capital(k, w, profits, capital):
    
    n = len(profits)
    projects = [(capital[i], profits[i]) for i in range(n)]
    projects.sort()
    max_heap = []
    i = 0
    for _ in range(k):
        # push to the priority queue 
        while i < n and projects[i][0] <= w:
            heapq.heappush(max_heap, -projects[i][1])
            i += 1

        if not max_heap:
            break

        w -= heapq.heappop(max_heap)

    return w



if __name__ == "__main__":
    k = 1
    w = 0 
    profits = [1,2,3] 
    capital = [1,1,2]

    print(maximize_capital(k, w, profits, capital))