from collections import defaultdict

class GfG:
    # Run a dfs on the original graph
    def DFS1(self, u, adj, visited, st):
        visited[u] = True
        for v in adj[u]:
            if not visited[v]:
                self.DFS1(v, adj, visited, st)
        st.append(u)  #while the dfs backtrack it saves the visited node, so that we effectively save the finish order of each node, during dfs 

    # DFS on reversed graph to collect SCC
    def DFS2(self, u, revAdj, visited, scc):
        visited[u] = True
        scc.append(u)
        for v in revAdj[u]:
            if not visited[v]:
                self.DFS2(v, revAdj, visited, scc)

    def kosaraju(self, V, adj):
        visited = [False] * V
        st = []

        # Fill stack with finish time order
        for i in range(V):
            if not visited[i]:
                self.DFS1(i, adj, visited, st)

        # print(st)

        # Reverse the graph
        # Reversing the graph prevent the second DFS to leak into other SCC starting from the highest node (the one which finished last to be visited)
        revAdj = [[] for _ in range(V)]
        for u in range(V):
            for v in adj[u]:
                revAdj[v].append(u)

        # print(revAdj)

        # Process reversed graph in order of stack
        visited = [False] * V
        SCCs = []

        while st:
            u = st.pop()
            if not visited[u]:
                scc = []
                self.DFS2(u, revAdj, visited, scc)
                SCCs.append(scc)

        return SCCs

if __name__ == "__main__":
    obj = GfG()
    V = 5
    edges = [
        [1, 3], [1, 4], [2, 1], [3, 2], [4, 5]
    ]

    adj = [[] for _ in range(V + 1)]
    for u, v in edges:
        adj[u].append(v)

    # print(adj)

    SCCs = obj.kosaraju(V + 1, adj)

    print("Strongly Connected Components:")
    for i in range(len(SCCs) - 1):
        for node in SCCs[i]:
            print(node, end=" ")
        print()