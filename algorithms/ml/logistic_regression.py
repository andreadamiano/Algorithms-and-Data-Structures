import numpy as np
import matplotlib
import  matplotlib.pyplot as plt
matplotlib.use("TkAgg")

class LogistRegression:
    def __init__(self, x, y):
        
        self.x = x 
        self.y = y
        self.n_samples, self.n_features = x.shape
        self.beta = np.random.randn() * 0.01  # Small random init
        self.omega = np.random.randn(self.n_features) * 0.01
        self.max_iter = 2000
        self.alpha = 0.15  # Smaller learning rate


    def cost(self, probs):
        """Cross entropy loss """
        eps = 1e-15
        probs = np.clip(probs, eps, 1 - eps)

        return -  (1/self.n_samples) * np.sum(self.y*np.log(probs) + (1-self.y)*np.log(1-probs))
    
    def sigmoid(self, z):
        return 1 / (1 + np.exp(-z))
    
    def predict(self):
        return (self.sigmoid(np.dot(self.x, self.omega) + self.beta) >= 0.5).astype(int)
    
    def compute_probs(self):
        return self.sigmoid(np.dot(self.x, self.omega) + self.beta)

    def train(self):
        i = 0
        prev_cost = float("inf")
        
        while (True):
            probs = self.compute_probs()
            current_cost = self.cost(probs)

            # if (current_cost / prev_cost < 1.001 or i > self.max_iter):
            if (i > self.max_iter):
                break 

            # Update parameters 
            errors = probs - self.y  # shape (200,)
            domega = np.dot(self.x.T, errors) / self.n_samples  # shape (2,)
            dbeta = np.mean(errors)  # scalar
            
            self.omega -= self.alpha * domega
            self.beta -= self.alpha * dbeta

            print(f"Iteration: {i}, COST: {current_cost}, current/ prev = {prev_cost /current_cost}")

            i += 1
            prev_cost = current_cost


# Fake dataset 
np.random.seed(42)
x = np.random.rand(200, 2) * 10
y = (x[:, 0] + x[:, 1] > 10).astype(int)

lr = LogistRegression(x, y)
lr.train()
y_hat = lr.predict()

plt.figure(figsize=(8, 6))
plt.scatter(x[:, 0], x[:, 1], c=y, cmap="bwr", alpha=0.6, label="Data")

# Decision boundary: omega[0]*x0 + omega[1]*x1 + beta = 0
x0_line = np.linspace(x[:, 0].min(), x[:, 0].max(), 100)
x1_line = -(lr.beta + lr.omega[0] * x0_line) / lr.omega[1]
plt.plot(x0_line, x1_line, "k--", linewidth=2, label="Decision boundary")

plt.xlabel("Feature 0")
plt.ylabel("Feature 1")
plt.legend()
plt.show()