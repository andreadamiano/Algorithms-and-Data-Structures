from typing import Callable

class Node:
    def __init__(self, data, _child_nodes = set() , _op = ''):
        self.data = data
        self.grad = 0    #this will accumulate gradients 
        self._backward:  Callable = lambda : None
        self._child_nodes = set(_child_nodes)
        self._op = _op
        
    def __add__ (self, other: 'Node'):
        out = Node(self.data + other.data, _child_nodes=(self, other), _op='+')

        def _backward():
            """Set the gradient of the children nodes using the chain rule"""
            ## formula: dL/da = dL/dout * dout/da
            ## where:
            ## dL/dout: the gradient flowing from the downstream (closer to the loss)
            ## dout/da: the local gradient, where out = (a + b) -> d(a + b)/da = 1 (how much the output of the current node changes if we change the input)
            ## L represent the loss function (which is compose of many smaller functions bulding the compotuational grapph)
            ## out is the output of the current node 
            self.grad += 1.0 * out.grad # accumulate gradients 
            other.grad += 1.0 * out.grad

        out._backward =_backward
        return out

    def __repr__(self):
        return f"Node(data={self.data}, grad={self.grad})"
    

    def __mul__(self, other: 'Node'):
        out = Node(self.data * other.data, _child_nodes=(self, other), _op= '*')

        def _backward():
            """
            Embed the partial derivative of the performed operation inside the output node, in order to accumulate gradient during backpropagation 
            """
            ## formula: dL/da = dL/dout * dout/da
            ## where:
            ## dL/dout: the gradient flowing from the downstream (closer to the loss)
            ## dout/da: the local gradient, where out = (a * b) -> d(a * b)/da = b
            self.grad += other.data * out.grad #total gradient is propagated updward the computational graph by multiplying the downstream gradient (which is accumulated by each node) and the local gradient (which is the partial derivative of the performed operation)
            other.grad += self.data * out.grad

        out._backward = _backward
        return out  

    def relu(self):
        out = Node(0 if self.data < 0 else self.data, _child_nodes=(self,), _op="ReLU")

        def _backward():
            ## formula: dL/da = dL/dout * dout/da
            ## where:
            ## dL/dout: the gradient flowing from downstream (closer to the loss) = out.grad
            ## dout/da: the local gradient of ReLU
            ## 
            ## For ReLU: 
            ##   if a > 0: out = a → dout/da = 1
            ##   if a <= 0: out = 0 → dout/da = 0
            self.grad += (out.data > 0) * out.grad  # Use += to accumulate gradients

        out._backward = _backward
        return out
    
    def _build_graph(self, node: "Node", graph: list = [], visited: set["Node"] = set()):
            """Perform post-order dfs to topological sort the computational graph, to get the order in which the nodes must be processed"""
    
            if node not in visited:
                visited.add(node)

                for child in node._child_nodes:
                    self._build_graph(child, graph, visited)
                
                graph.append(node)  #post order traversal 

            return graph
    
    def backward(self):

        graph = self._build_graph(self)
        print(f"Computed graph: {graph}")   
        
        #visit each node in the computed topological order (reversed) and accumulate gradients
        self.grad = 1.0 #initialize the gradient of the last node of the computational graph  
        for node in reversed(graph):
            node: Node
            print(node)
            node._backward()
            print(f"after _backward: {[x for x in node._child_nodes]}")
        

if __name__ == "__main__":
    print("=== EXAMPLE 1: Simple Expression ===")
    #f(x, y) = (x + y) * x
    x = Node(2.0)
    y = Node(3.0)
    
    #forward pass
    a = x + y      
    b = a * x  
    
    print("Forward pass:")
    print(f"x = {x.data}, y = {y.data}")
    print(f"a = x + y = {a.data}")
    print(f"b = a * x = {b.data}")
    
    #backward pass
    b.backward()
    
    print("\nBackward pass:")
    print(f"∂b/∂x = {x.grad}")
    print(f"∂b/∂y = {y.grad}")
    
    print("\nManual verification:")
    print(f"Expected ∂b/∂x = 2x + y = {2*x.data + y.data}")
    print(f"Expected ∂b/∂y = x = {x.data}")
    
    print("\n" + "="*50)
    
    # print("=== EXAMPLE 2: With ReLU ===")
    # # Let's compute: f(x, y) = ReLU(x * y) + x
    # # Where x = -1, y = 4
    # x2 = Node(-1.0)
    # y2 = Node(4.0)
    
    # # Forward pass
    # c = x2 * y2    # c = -1 * 4 = -4
    # d = c.relu()   # d = ReLU(-4) = 0
    # e = d + x2     # e = 0 + (-1) = -1
    
    # print("Forward pass:")
    # print(f"x = {x2.data}, y = {y2.data}")
    # print(f"c = x * y = {c.data}")
    # print(f"d = ReLU(c) = {d.data}")
    # print(f"e = d + x = {e.data}")
    
    # # Backward pass
    # e.backward()
    
    # print("\nBackward pass:")
    # print(f"∂e/∂x = {x2.grad}")
    # print(f"∂e/∂y = {y2.grad}")
    
    # # Manual verification:
    # # e = ReLU(x*y) + x
    # # Since x*y = -4 < 0, ReLU(x*y) = 0, so e = 0 + x = x
    # # ∂e/∂x = 1 (from the + x part) + 0 (from ReLU since input < 0)
    # # ∂e/∂y = 0
    
    # print("\nManual verification:")
    # print(f"Expected ∂e/∂x = 1")
    # print(f"Expected ∂e/∂y = 0")
    
    # print("\n" + "="*50)
    
    # print("=== EXAMPLE 3: Complex Expression ===")
    # # Let's compute: f(x, y, z) = ReLU(x + y) * z
    # # Where x = 1, y = -2, z = 3
    # x3 = Node(1.0)
    # y3 = Node(-2.0) 
    # z3 = Node(3.0)
    
    # # Forward pass
    # f1 = x3 + y3    # f1 = 1 + (-2) = -1
    # f2 = f1.relu()  # f2 = ReLU(-1) = 0
    # f3 = f2 * z3    # f3 = 0 * 3 = 0
    
    # print("Forward pass:")
    # print(f"x = {x3.data}, y = {y3.data}, z = {z3.data}")
    # print(f"f1 = x + y = {f1.data}")
    # print(f"f2 = ReLU(f1) = {f2.data}")
    # print(f"f3 = f2 * z = {f3.data}")
    
    # # Backward pass
    # f3.backward()
    
    # print("\nBackward pass:")
    # print(f"∂f3/∂x = {x3.grad}")
    # print(f"∂f3/∂y = {y3.grad}") 
    # print(f"∂f3/∂z = {z3.grad}")
    
    # # Manual verification:
    # # Since f1 = -1 < 0, ReLU(f1) = 0, so f3 = 0
    # # All gradients should be 0
    
    # print("\nManual verification:")
    # print("All gradients should be 0 since output is constant 0")