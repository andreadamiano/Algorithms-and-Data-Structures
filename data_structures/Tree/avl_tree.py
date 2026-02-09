class Node:
    def __init__(self, data, parent):
        self.data = data
        self.parent = parent
        self.right = None
        self.left = None
        self.height = 1


class AvlTree:
    def __init__(self):
        self.root = None

    def getHeight(self, node: Node):
        return node.height if node else 0

    def getBalance(self, node: Node):
        return self.getHeight(node.left) - self.getHeight(node.right) if node else 0
    
    def rotateLeft(self, node: Node):
        #update children
        child: Node = node.right 
        node.right = child.left
        child.left = node

        #update parents
        child.parent = node.parent
        node.parent = child

        if node.right:
            node.right.parent = node

        #update heights
        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        child.height = 1 + max(self.getHeight(child.left), self.getHeight(child.right))
        return child
    
    def rotateRight(self, node: Node):
        #update children
        child: Node = node.left
        node.left = child.right
        child.right = node

        #update parents
        child.parent = node.parent 
        node.parent = child 

        if node.left:
            node.left.parent = node

        #update heights
        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        child.height = 1 + max(self.getHeight(child.left), self.getHeight(child.right))
        return child
    
    def rebalance_tree(self, node: Node):
        balance = self.getBalance(node)

        #left-left
        if balance > 1 and self.getBalance(node.left) >= 0: 
            return self.rotateRight(node)

        #left-right 
        if balance > 1 and self.getBalance(node.left) < 0:
            node.left = self.rotateLeft(node.left)
            return self.rotateRight(node)
        
        #right-left 
        if balance < -1 and self.getBalance(node.right) >= 0:
            node.right = self.rotateRight(node.right)
            return self.rotateLeft(node)
        
        #right-right 
        if balance < -1 and self.getBalance(node.right) < 0:
            return self.rotateLeft(node)
        
        return node 
    
    def insertNode(self, node: Node, data, parent: Node = None):
        if not node: 
            return Node(data, parent)
        
        if node.data > data:
            node.left = self.insertNode(node.left, data, node)
        
        elif node.data < data:
            node.right = self.insertNode(node.right, data, node)

        elif node.data == data:
            return node 

        #update height 
        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        return self.rebalance_tree(node) #fix insertion

    def insert(self, data):
        self.root = self.insertNode(self.root, data)
        return 
    
    def inorder_successor(self, node: Node):
        while node.left:
            node = node.left

        return node
    
    def deleteNode(self, node: Node, data):
        if not node:
            return node #node not found
        
        if node.data > data:
            node.left = self.deleteNode(node.left, data)

        elif node.data < data:
            node.right = self.deleteNode(node.right, data)
        
        else:
            #node found
            if not node.left:
                return node.right
            
            if not node.right:
                return node.left
            
            else: #node with 2 children
                successor = self.inorder_successor(node.right)
                node.data = successor.data
                node.right = self.deleteNode(node.right, node.data)
        
        #update height
        node.height = 1 + max(self.getHeight(node.left), self.getHeight(node.right))
        return self.rebalance_tree(node) #ifx deletion
    
    def delete(self, data):
        self.deleteNode(self.root, data)
        return


if __name__ == "__main__":
    tree = AvlTree()
    tree.insert('A')
    tree.insert('B')
    tree.insert('D')
    tree.insert('C')
    tree.insert('E')
    tree.delete('B')