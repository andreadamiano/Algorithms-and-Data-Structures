from collections import defaultdict

class Node:
    def __init__(self, value):
        self.value = value
        self.parent: Node = None
        self.size = 0

class Partition:
    def __init__(self):
        self.nodes = {}

    def add_node(self, value):
        node = Node(value)
        node.parent = node
        node.size += 1
        self.nodes[value] = node

    def union(self, left_val, right_val):
        root_a = self.find(self.nodes[left_val])
        root_b = self.find(self.nodes[right_val])

        if root_a == root_b:
            return root_a
        
        if root_a.size < root_b.size: #make sure root a is the bigger one
            root_a, root_b = root_b, root_a

        root_b.parent = root_a
        root_a.size += root_b.size
        return root_a


    def find(self, node: Node):
        if node.parent == node:
            return node
        
        node.parent = self.find(node.parent) #path compression
        return node.parent


def find_good_paths(vals: list[int], edges: list[list]):
    
    #build adjcency list 
    adj = defaultdict(list)
    for source, destination in edges:
        adj[source].append(destination)
        adj[destination].append(source)

    #map every value to the corresponding node
    #initialize every partition
    val_to_nodes = defaultdict(list)
    partition = Partition()
    for i, val in enumerate(vals):
        val_to_nodes[val].append(i)
        partition.add_node(i)

    result = 0
    #process every values in ascending order (in order to be greedy)
    for i in sorted(val_to_nodes.keys()):
        for source_node in val_to_nodes[i]:

            #iterate over all possible nodes connected to the current node
            for destination_node in adj[source_node]:
                if vals[source_node] > vals[destination_node]:
                    partition.union(source_node, destination_node)

        group_counts = defaultdict(int)
        for node in val_to_nodes[i]:
            root_node = partition.find(partition.nodes[node])
            group_counts[root_node] += 1 #count how many nodes belong to the same connecte component
            result += group_counts[root_node] #if 2 nodes belong to the same connected components they are part of a good path since we are processing the nodes in ascending order

    return result


if __name__ == "__main__":
    vals = [1,3,2,1,3]
    edges = [[0, 1], [0, 2], [2, 3], [2, 4]]
    print(find_good_paths(vals, edges))
