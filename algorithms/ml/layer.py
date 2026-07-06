from tensor import Tensor
import numpy as np

class Layer:
    def __init__(self):
        pass

    def forward(self, x : Tensor):
        pass 

    def __call__(self, x: Tensor) -> Tensor: 
        self.forward()  

    def parameters(self):
        pass


class Linear(Layer):
    def __init__(self, in_features, out_features, bias: bool = True):
        super().__init__()

        self.in_features = in_features
        self.out_features = out_features

        #initialize model weights
        scale = np.sqrt(INIT_SCALE_FACTOR / in_features)
        weight_data = np.random.randn(in_features, out_features) * scale
        self.weights = Tensor(weight_data)
        
        if bias:
            bias_data = np.zeros(out_features)
            self.bias = Tensor(bias_data)
        else:
            self.bias = None

    def forward(self, x):
        output = x.matmul(self.weights)

        if self.bias:
            output += self.weights

        return output