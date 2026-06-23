import numpy as np

class Tensor:
    def __init__(self, data, requires_grad = True):
        self.data = np.array(data) #wrap data into numpy objects 
        self.shape = self.data.shape
        self.size = self.data.size
        self.requires_grad = requires_grad

    def __add__(self, other):
        """
        Add 2 tensors element wise, while supporting broadcasting
        The general rule is that: shapes are compared from right to left, broadcasting is allowed only if they’re equal or if one of them is 1 (missing dimensions are treated as 1)
        """
        if isinstance(other, Tensor):
            return Tensor(self.data + other.data) #numpy will handle broadscasting

        else: #scalar
            return Tensor(self.data + other)  #scalar broadcasting
        
    def matmul(self, other: "Tensor"):
        if not isinstance(other, Tensor):
            raise Exception(f"Expected tensor for matrix multiplication, got {type(other)}")
        
        #shape validation: inner shapes should match
        if len(self.shape) >= 2 and len(other.shape) >= 2:
            if self.shape[-1] != other.shape[-2]: #the other dimensions on the left are treated as batch dimensions 
                raise Exception(f"Cannot perform matri mulitplication: {self.data} @ {other.data}, since inner dimensions doesnt match: {self.shape[-1]} != {other.shape[-2]}")
            
        result = np.matmul(self.data, other.data)
        return Tensor(result)
    
    def reshape(self, *shape):
        """Reshape the tensor to new dimensions"""
        if len(shape) == 1 and isinstance(shape[0], (tuple, list)):
            new_shape = tuple(shape[0])
        else:
            new_shape = shape
        
        
        #handle -1 for automatic dimension inference
        if -1 in new_shape:
            #first compute the known dimension provided as input 
            known_size = 1
            unknown_index = new_shape.index(-1) #get the index of the -1 value in the new shape provided

            for index, dimension in enumerate(new_shape):
                if index != unknown_index:
                    known_size *= dimension

            unkown_dimension = self.size // known_size
            new_shape = list(new_shape)
            new_shape[unknown_index] = unkown_dimension
            new_shape = tuple(new_shape)

        #validation
        if np.prod(new_shape) != self.size:
            raise Exception(f"Cannot reshape {self.shape} into {new_shape}, element count mismatch")
        
        reshaped_data = np.reshape(self.data, new_shape)
        return Tensor(reshaped_data)
    
    def sum(self, axis = None, keepdims = False):
        """Sum tensor along the specified axis"""
        result = np.sum(self.data, axis=axis, keepdims=keepdims)
        return Tensor(result)
    
    def mean(self, axis = None, keepdims = False):
        """Sum tensor along the specified axis"""
        result = np.mean(self.data, axis=axis, keepdims=keepdims)
        return Tensor(result)
    
    def __truediv__(self, other: "Tensor"):
        if isinstance(other, "Tensor"):
            return Tensor(self.data / other.data)
        raise Exception(f"Division between {type(self)} and {type(other)} not supported.")
    
    def __mul__(self, other):
        if isinstance(other, "Tensor"):
            return Tensor(self.data * other.data)
        raise Exception(f"Multiplication between {type(self)} and {type(other)} not supported.")
    
    @property
    def T(self):
        result = self.data.T
        return Tensor(result)
    

         

if __name__ == "__main__":
    import sys
    print(sys.path[0])

    #test broadcasting operations
    x = Tensor([[1, 2, 3],[4,5,6]])
    y = Tensor([1,2,3])
    z = x + y
    # z = x + 5
    print(z.data)

    #test reshape and matrix multiplications
    y.reshape(-1,1) #reshape into a column vector 
    z = x.matmul(y)
    print(z.data)
    
    #test transpose
    print(x.T.data)