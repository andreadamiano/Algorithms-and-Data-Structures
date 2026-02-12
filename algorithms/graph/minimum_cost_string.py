
def minimumCost(source, target, original, changed, cost):
    INF = 10**30
    id = {}
    lens = set()
    incremental_id = 0

    dist = [[INF]*201 for _ in range(201)]

    #assign an id to every node (which is actually a string)
    for s, t, c in zip(original, changed, cost):
        if s not in id:
            id[s] = incremental_id
            lens.add(len(s))
            incremental_id += 1
        if t not in id:
            id[t] = incremental_id
            incremental_id += 1
        dist[id[s]][id[t]] = min(dist[id[s]][id[t]], c)

    #initialize the dp table of the floyd wharshall algorithm
    for i in range(incremental_id):
        dist[i][i] = 0

    #compute the shortest path of each node to each node 
    for k in range(incremental_id):
        for i in range(incremental_id):
            if dist[i][k] < INF:
                for j in range(incremental_id):
                    if dist[k][j] < INF:
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    n = len(source)
    dp = [INF] * (n + 1)
    dp[0] = 0  #represent the cost to convert source[:i] to target[:i]

    for i in range(n):
        if dp[i] == INF:
            continue

        #if the 2 char are already identical no need to convert and to spend anything 
        if source[i] == target[i]:
            dp[i + 1] = min(dp[i + 1], dp[i])

        for L in lens:
            if i + L > n:
                continue
            s = source[i:i+L]
            t = target[i:i+L]
            if s in id and t in id:
                dp[i + L] = min(dp[i + L], dp[i] + dist[id[s]][id[t]])

    return -1 if dp[n] == INF else dp[n]


if __name__ == "__main__":
    source = "abcdefgh"
    target = "acdeeghh"
    original = ["bcd","fgh","thh"]
    changed = ["cde","thh","ghh"] 
    cost = [1,3,5]
    print(minimumCost(source, target, original, changed, cost))