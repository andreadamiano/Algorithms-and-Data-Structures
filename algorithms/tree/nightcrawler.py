from collections import defaultdict
import heapq

def max_partition(n, vertices, parents):
    n = len(vertices)

    adj_list = defaultdict(list)
    for index, parent in enumerate(parents):
        adj_list[parent].append(index + 2)

    split_gains = []

    def dfs(node):
        """
        The main idea is to traverse the tree, while collecting all the best indepedent paths
        at each node interesction merge the current parent node with the child node with the lower path value, this greedy approach ensure that the overall partition that will be generated has the highest possible value
        before merging the selected child with the parent, compute the split gain , meaning the gain we would get by splitting the current chilld node with the parent node
        this split gain would be used when we need to compute the best value of the partition for a number ofsubsets higher the the number of indipendent paths founded during the tree traversal
        """

        #collect child heaps before mergin them
        child_heaps = [] 
        current_heap = []
        biggest_child_heap_index = 0
        biggest_child_heap_len = 0

        if not adj_list[node]:
            return [vertices[node-1]]

        for index, neighbor in enumerate(adj_list[node]):
            child_heap = dfs(neighbor)
            child_heaps.append(child_heap)
            if len(child_heap) > biggest_child_heap_len:
                biggest_child_heap_index = index
                current_heap = child_heap


        #merge child heaps starting from the biggest one (to imporve time complexity)
        for i in range(len(child_heaps)):
            if i == biggest_child_heap_index:
                continue

            while child_heaps[i]:
                item = heapq.heappop(child_heaps[i])
                heapq.heappush(current_heap, item)


        #after having merged the child heaps merge the smallest independent path with the parent node
        item = heapq.heappop(current_heap) 

        #before merging compute the split gain we would have if we decide to split instead of merge 
        heapq.heappush(split_gains, -min(item, vertices[node-1])) #push the negative value to make this a max heap 

        #store once again the independent path generated merging the min child indepentend path with the parent
        heapq.heappush(current_heap, max(item, vertices[node-1]))


        return current_heap

    indipendent_paths = dfs(1) #start from the root
    len_indipendent_paths = len(indipendent_paths)
    result = [-1 for _ in range(n)]
    result[len_indipendent_paths-1] = sum(indipendent_paths)

    for i in range(len_indipendent_paths, len_indipendent_paths + len(split_gains)):
        result[i] = result[i-1] - heapq.heappop(split_gains)  #use - since split gains store negative values

    return result
        


if __name__ == "__main__":
    n = 4
    vertices = [5, 10, 15, 20]
    parents = [1, 2, 2] #parents of the vertics from the second vertex 

    # n = 3
    # vertices = [10, 20, 30]
    # parents = [1, 1] #parents of the vertics from the second vertex 
    
    print(max_partition(n, vertices, parents))

