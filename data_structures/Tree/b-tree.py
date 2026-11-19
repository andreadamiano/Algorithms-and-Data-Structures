class Node: 
    
    def __init__(self, parent, key, value = None):
        self.parent = parent 
        self.children: dict 
        self.key = key
        self.value = value
        self.external = False if value else True

    def add_child(self, )

class BTree:
    """
    This data structure achieves 2 main goals:
    - size properties: every internal nodes should have at most x children 
    - depth property:  all external nodes shouls have the same depth (keeping the height at O(log(n)))
    enforcing this 2 properties is enough to keep the tree well balanced
    """

    def __init__(self):
        self.MAX_CHILDREN = 4

    def insert(self, node: Node):
        pass 