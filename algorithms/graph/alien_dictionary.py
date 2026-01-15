from typing import Dict
import heapq


class Node:
    def __init__(self, char):
        self.char = char
        self.parents = set()
        self.children = set()
        self.in_degree = 0
        self.out_degree = 0 

    def add_parent(self, parent):
        self.parents.add(parent)
    
    def add_child(self, child):
        self.children.add(child)

    def __str__(self):
        return f"{self.char}"

    def __hash__(self):
        return hash(self.char)
    
    def __eq__(self, other: "Node"):
        return self.char == other.char
    
    def __lt__ (self, other: "Node"):
        return self.in_degree < other.in_degree

class Edge:
    def __init__(self, start_node, end_node):
        self.start_node = start_node
        self.end_node = end_node

    def __str__(self):
        return f"{self.start_node.char} - {self.end_node.char}"

class Graph:
    def __init__(self):
        self.edge_list = []
        self.nodes: Dict[chr, Node] = dict()

    def add_edge(self, start_char, end_char):
        if start_char not in self.nodes:
            self.nodes[start_char] = Node(start_char)
        if end_char not in self.nodes:
            self.nodes[end_char] = Node(end_char)
        node1 = self.nodes[start_char]
        node2 = self.nodes[end_char]
        node2.add_parent(node1)
        node1.add_child(node2)
        self.edge_list.append(Edge(node1, node2))

def foreign_dictionary(words):
    result = ""
    graph = Graph()
    n = len(words)
    for i in range(1, n):
        #compare the current word with the previous 
        word_prev, word_curr = words[i-1] , words[i]
        l1 , l2 = len(word_prev), len(word_curr)
        for j in range(min(l1, l2)):
            if word_prev[j] != word_curr[j]:
                graph.add_edge(word_prev[j], word_curr[j])
                break

    #create DAG
    heap = []
    for node in graph.nodes.values():
        node: Node
        if not node.parents:
            heapq.heappush(heap, node)

    while heap:
        current_node: Node
        current_node = heapq.heappop(heap)
        current_node.in_degree -= 1
        
        for out_node in current_node.children:
            heapq.heappush(heap, out_node)
        
        if current_node.in_degree > 0:
            heapq.heappush(heap, current_node)
        
        else:
            result += f"{current_node.char}"
            
    
    return result

if __name__ == "__main__":
    words = ["hrn","hrf","er","enn","rfnn"]
    print(foreign_dictionary(words))