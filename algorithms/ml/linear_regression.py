import matplotlib
import  matplotlib.pyplot as plt
import numpy as np
matplotlib.use("TkAgg")

class StandardScaler:
    def __init__(self):
        self.mean = None
        self.std = None

    def fit(self, data):
        self.mean = np.mean(data)
        self.std = np.std(data)
        self.std = np.where(self.std == 0, 1e-8, self.std)  #cap to 1e-8 in order to prevent division per 0

    def transform(self, data):
        if self.mean and self.std:
            return (data - self.mean) / self.std
        else:
            raise Exception("Fit the data before applying transform")
        
    def fit_transform(self, data):
        self.fit(data)
        return self.transform(data)
    
    def inverse_transform(self, scaled_data):
        """Denormalize back to original scale"""
        return (scaled_data * self.std) + self.mean


class LinearRegressor:
    def __init__(self, max_iter = 1000, alpha = 0.01):

        #randomly initialize the coefficient of the model
        self.beta = np.random.randn() * 0.01 
        self.omega = np.random.randn() * 0.01

        #parameters of the model
        self.max_iter = max_iter
        self.alpha = alpha  #learning rate

    def mse (self, y, predictions):
        return (1/(2*len(y))) * np.sum((y - predictions)**2)

    def predict (self, x):
        return  self.omega + self.beta * x
    
    def train(self, x, y):
        n = len(x)
        i = 0
        prev_mse = float("inf")
        
        while (True):
            y_hat = self.predict(x)
            current_mse = self.mse(y, y_hat)

            if (current_mse / prev_mse > 0.999 or i > self.max_iter):
                break 

            #compute the gradients of the cost function with respect to the coefficients of the model
            domega = np.sum(y_hat - y) / n     # ∂J/∂ω
            dbeta = np.dot(y_hat - y, x) / n   # ∂J/∂β

            #update the coefficient of the model stepping in the direction of the computed gradient
            self.omega -= self.alpha * domega
            self.beta -= self.alpha * dbeta

            print(f"Iteration: {i}, MSE: {current_mse}, current/ prev = {current_mse /prev_mse}")

            i += 1
            prev_mse = current_mse


class MultivariateLinearRegressor:
    def __init__(self, max_iter=2000, alpha=0.1):
        self.weights = None  #this matrix will hold both bias and coefficients
        self.max_iter = max_iter
        self.alpha = alpha  

    def _add_bias(self, X):
        """Adds a column of 1s to the matrix X (The Bias Trick) to ensure the computed hyperplane is not stricly at the origin"""
        bias_column = np.ones((X.shape[0], 1))
        return np.hstack((bias_column, X))

    def mse(self, y, predictions):
        return (1 / (2 * len(y))) * np.sum((y - predictions) ** 2)

    def predict(self, X):
        #if the input doesn't have the bias column yet, add it
        if X.shape[1] == self.weights.shape[0] - 1:
            X = self._add_bias(X)
        return np.dot(X, self.weights)
    
    def train(self, X: np, y):
        n, num_features = X.shape
        X_with_bias = self._add_bias(X)
        
        #random intialize the weights vector (num_features + 1 for the bias)
        self.weights = np.random.randn(num_features + 1, 1) * 0.01
        
        prev_mse = float("inf")
        
        for i in range(self.max_iter):
            y_hat = np.dot(X_with_bias, self.weights)
            current_mse = self.mse(y, y_hat)

            if current_mse / prev_mse > 0.9999:
                break 

            #compute the gradient of the mse with respect to the weights vector
            dweights = np.dot(X_with_bias.T, (y_hat - y)) / n

            #update the weights vector in the direction of the computed gradient 
            self.weights -= self.alpha * dweights

            #log current iteration
            print(f"Iteration: {i}, MSE: {current_mse}")

            prev_mse = current_mse
            

if __name__ == "__main__":
    #generate a fake dataset
    x = np.arange(1, 100)
    y = x*3 +5
    y = y + np.random.randint(-30, 30, size=len(y)) #add random noise to the dependent variable 

    #split the data into train and test sets
    x_train = x[:80]
    y_train = y[:80]
    x_test = x[80:]
    y_test = y[80:]

    #normalize training set 
    y_scaler = StandardScaler()
    x_scaler = StandardScaler()
    x_train_normalized = x_scaler.fit_transform(x_train)
    y_train_normalized = y_scaler.fit_transform(y_train)

    #train model
    lr  = LinearRegressor()
    lr.train(x_train_normalized, y_train_normalized)

    #generate predictions
    x_test_normalized = x_scaler.transform(x_test)
    predictions_normalized = lr.predict(x_test_normalized)
    predictions = y_scaler.inverse_transform(predictions_normalized)
    mse = lr.mse(y_test, predictions)

    #plot
    plt.scatter(x_test, y_test)
    plt.plot(x_test, predictions, "r")
    plt.scatter(x_train, y_train)
    plt.show()
    print(mse)


    #non-linear curve test
    
    #generate a nonlinear curve 
    x = np.arange(1, 100)
    y = 0.5 * (x**2) + 3 * x + 25 
    y = y + np.random.randint(-150, 150, size=len(y)) #add noise
    
    #reshape the vector to be acolumn vector (instead of a row vector)
    y = y.reshape(-1, 1)
    
    #generate multiple features
    #feature 1: x
    #feature 2: x^2
    X = np.column_stack((x, x**2))

    #split data into train and test sets
    X_train, X_test = X[:80], X[80:]
    y_train, y_test = y[:80], y[80:]

    #normalize data
    x_scaler = StandardScaler()
    y_scaler = StandardScaler()
    
    X_train_scaled = x_scaler.fit_transform(X_train)
    y_train_scaled = y_scaler.fit_transform(y_train)

    #train model
    lr = MultivariateLinearRegressor()
    lr.train(X_train_scaled, y_train_scaled)

    #predict
    X_test_scaled = x_scaler.transform(X_test)
    predictions_scaled = lr.predict(X_test_scaled)
    predictions = y_scaler.inverse_transform(predictions_scaled)
    
    #plot
    plt.scatter(X_train[:, 0], y_train, color='gray', label="Train Data")
    plt.scatter(X_test[:, 0], y_test, color='blue', label="Test Data")
    plt.plot(X_test[:, 0], predictions, "r-", linewidth=3, label="Multivariate Prediction")
    plt.legend()
    plt.show()
            

