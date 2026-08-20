from collections import defaultdict

def mist(nodes: list, parents: list):

    adjency_dict = defaultdict(list)

    for index, parent in enumerate(parents):
        adjency_dict[parent].append(nodes[index+1])

    print(adjency_dict)

    def dfs(node):

        if node not in adjency_dict:
            return 0, 1

        indipendent_sets_skip = 0 #the number of inidipendent sets if the current node is skipped
        indipendent_sets_include = 0 #the number of inidipendent sets if the current node is included 
        for neighbor in adjency_dict[node]:
            skip, include = dfs(neighbor)
            indipendent_sets_skip += max(include, skip)
            indipendent_sets_include += skip


        return indipendent_sets_skip, indipendent_sets_include + 1

    
    #run dfs from the rooted node
    return max(dfs(nodes[0]))

    

if __name__ == "__main__":
    nodes = [7, 5, 10, 40, 20, 30]
    parents = [7, 5, 5, 10, 10]
    print(mist(nodes, parents))