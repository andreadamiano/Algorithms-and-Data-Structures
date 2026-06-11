from collections import defaultdict

def parallel_courses(n, relations, time):

    cache = {}
    def dfs(node):
        if node in cache:
            return cache[node]

        tot_time = time[node-1]
        for neighbor in adj_list[node]:
            tot_time = max(tot_time, dfs(neighbor) + tot_time)

        cache[node] = tot_time
        return cache[node]


    adj_list = defaultdict(list)

    for edge in relations:
        adj_list[edge[0]].append(edge[1])

    for node in range(1, n+1):
        dfs(node)

    return max(cache.values())
    


if __name__ == "__main__":
    n = 3
    relations = [[1,3],[2,3]]
    time = [3,2,5]
    print(parallel_courses(n, relations, time))