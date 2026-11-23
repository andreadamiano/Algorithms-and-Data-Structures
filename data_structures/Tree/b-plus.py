import bisect

MAX_CHILDREN = 3

class Node: 
    
    def __init__(self, external, parent = None, prev = None, next = None):
        self.parent = parent 
        self.children_keys = [float("inf")] * MAX_CHILDREN  #both array must be sorted to allow O(log(n)) traversal with binary search
        self.children = [float("inf")] * (MAX_CHILDREN + 1) #internal nodes can store up to m+1 children with m keys, while the mapping is 1:1 for external nodes  
        self.prev = prev #linked list of external nodes to allow horizzontal traversing
        self.next = next
        self.external = external 
        self.size = 0

    def insert(self, key, value):
        index = bisect.bisect_left(self.children_keys, key)

        if index < self.size and self.children_keys[index] == key: #if the key is already present change only the value
            self.children[index] = value
            return

        self.children_keys = self.children_keys[:index] + [key] + self.children_keys[index:]
        self.children = self.children[:index] + [value] + self.children[index:]
        self.size += 1 

    def insert_value(self, key, value):
        index = bisect.bisect_left(self.children_keys, key)
        self.children = self.children[:index] + [value] + self.children[index:]

        #connect leaf nodes
        if isinstance(value, Node) and value.external:
            prev:Node = self.children[index - 1] if index - 1 >= 0 else None
            next:Node = self.children[index + 1] if index + 1 <= MAX_CHILDREN + 1  else None
            if prev:
                value.prev = prev
                prev.next = value

            if isinstance(next, Node):
                value.next = next
                next.next = value

    def insert_key(self, key):
        index = bisect.bisect_left(self.children_keys, key)
        self.children_keys = self.children_keys[:index] + [key] + self.children_keys[index:]
        self.size += 1 

    def split(self):
        median = (MAX_CHILDREN + 1) // 2
        median_key = self.children_keys[median]
        tmp_children_keys = self.children_keys[median:MAX_CHILDREN+2]
        tmp_children = self.children[median:MAX_CHILDREN+2]
        self.children_keys = self.children_keys[:median]
        self.children = self.children[:median]
        self.size = median

        #create split node 
        split = Node(external=self.external)
        split.parent = self.parent
        split.children_keys = tmp_children_keys
        split.children = tmp_children
        split.size = MAX_CHILDREN + 1 - median
        return median_key, split

class BPlusTree:
    """
    This data structure achieves 2 main goals:
    - size properties: every internal nodes should have at most x children 
    - depth property:  all external nodes shouls have the same depth (keeping the height at O(log(n)))
    enforcing this 2 properties is enough to keep the tree well balanced
    The b+ tree is a variant of the b-tree, where key value paris are stored only at the leaves, while internal nodes acts as routing nodes,
    moreover leaves are linked to each others in order to iterate over them. 
    """

    def __init__(self):
        self.root = Node(external=True) #initialize the root as an external node 

    def insert(self, key, value, current: Node = None):
        current: Node = self.root if not current else current 

        if current.external: 
            current.insert(key, value) #always allow insertion, then check if the insertion as overflown, this allow to rebalance while bubbling up  
            self._check_node(current)

        else:
            index = bisect.bisect_right(current.children_keys, key)
            self.insert(key, value, current.children[index])
            self._check_node(current) #always check the node while bubling up

    def _check_node(self, node: Node):
        if node.size <= MAX_CHILDREN:
            return

        median_key, split = node.split()
        parent: Node = node.parent

        if not parent:
            parent = Node(external=False)
            parent.insert_value(median_key, node)

            self.root = parent
            node.parent = parent
            split.parent = parent

        parent.insert_key(median_key) #insert routing key
        parent.insert_value(median_key + 1, split)
        

if __name__ == "__main__":
    tree = BPlusTree()
    tree.insert(10, 10)
    tree.insert(5, 5)
    tree.insert(12, 12)
    tree.insert(1, 1) #split
    tree.insert(2, 2)
    tree.insert(25, 25)
    tree.insert(0, 0) #split
    tree.insert(4, 4) 
    tree.insert(3, 3) #split
    tree.insert(6, 6) 
    tree.insert(7, 7) 
    tree.insert(4,4)