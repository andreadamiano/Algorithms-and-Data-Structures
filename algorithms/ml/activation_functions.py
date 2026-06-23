from tensor import Tensor
import numpy as np


class ReLU:
    def forward(self, x: Tensor) -> Tensor:
        """It zeros out negative numbers"""
        result = np.maximum(0, x.data)
        return Tensor(result)
    
    def __call__(self, x: Tensor):
        return self.forward(x)


class Sigmoid:
    def forward(self, x: Tensor) -> Tensor:
        """Maps any real number to a range (0,1)"""
        #clip data 
        z = np.clip(x, -500, 500)

        #initialize results
        result = np.zeros_like(z)

        #apply the same formula while preventing floating point numbers overflow
        #1 / (1 + exp(-x))
        positive_mask = z >= 0
        result[positive_mask] = 1.0 / (1.0 + np.exp(-z[positive_mask]))

        #1 / (1 + exp(-x)) * exp(x)/exp(x), this trik will prevent overflow for negative numbers
        negative_mask = z < 0
        exp_z = np.exp(z[negative_mask])
        result[negative_mask] = exp_z / (1.0 + exp_z)

        return Tensor(result)
    
    def __call__(self, x: Tensor):
        return self.forward(x)
    

class Tahn: 
    """Maps any real number to a range (-1,1)"""
    def forward(self, x: Tensor) -> Tensor:
        result = np.tanh(x)
        return Tensor(result)
    
    def __call__(self, *args, **kwds):
        return self.forward(x)


class GeLu:
    def forward(self, x: Tensor) -> Tensor:
        """Maps any real number to a range roughly [-0.17, +inf], computed using the fast sigmoid approximation"""
        return Sigmoid()(x * 1.702) * x

    def __call__(self, x: Tensor):
        return self.forward(x)


class Softmax:
    def forward(self, x: Tensor, dim:int = 1) -> Tensor:
        """Converts any vector into a probability distribution, summing to one"""
        #subtract max for numerical stability and preventing overflow
        x_max_data = np.max(x.data, axis=dim, keepdims=True)
        x_max = Tensor(x_max_data, requires_grad=False)
        x_shifted: Tensor = x - x_max

        exp_values = Tensor(np.exp(x_shifted.data)) 
        exp_sum_data = np.sum(exp_values.data, axis=dim, keepdims=True)
        exp_sum = Tensor(exp_sum_data, requires_grad=x_shifted.requires_grad)

        result = exp_values / exp_sum
        return result
    
    def __call__(self, x: Tensor):
        return self.forward(x)
    


if __name__ == "__main__":
    x = Tensor([[-1, 0, 1, 2]])
    relu = ReLU()
    z = relu(x)
    print(z.data)