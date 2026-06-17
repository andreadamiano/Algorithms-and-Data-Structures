import matplotlib
import  matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict
matplotlib.use("TkAgg")


class Cluster:
    def __init__(self, n_clusters , max_iter = 300):
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.centroids = None

    def _euclidean_distance(self, X,centroids):
        #cartesian product (compute the difference between all possible combination of centroid and point)
        return np.linalg.norm(X[:, np.newaxis] - centroids, axis=2) #vectorized operation (leveraging broadcasting in mumpy)
    
    def _compute_centroid(self, X: np.matrix, clusters: np.matrix):
        #zero initialize the centroids matrix
        centroids = np.zeros((self.n_clusters, X.shape[1]))
        
        for k in range(self.n_clusters):
            mask = (clusters == k)
            cluster_points = X[mask]
            
            if len(cluster_points) > 0:
                centroids[k] = np.mean(cluster_points, axis=0)
            else:
                centroids[k] = X[np.random.choice(X.shape[0])]
                
        return centroids
    
    def _compute_clusters(self, X: np.matrix, centroids: np.matrix):
        #compute the euclidean distance of each point with each centroid
        distances = self._euclidean_distance(X, centroids) 

        #assign each node to the nearest centroid
        return np.argmin(distances, axis=1)


    def fit(self, X: np.matrix):
        #initialize centroids
        centroids_indices = np.random.choice(X.shape[0], size=self.n_clusters, replace=False)
        centroids = X[centroids_indices]
        converged = False
        iterations = 0

        while not converged:

            clusters = self._compute_clusters(X, centroids)
            new_centroids = self._compute_centroid(X, clusters)
                
            if np.allclose(centroids, new_centroids) or iterations < self.max_iter:
                converged = True


            centroids = new_centroids
            iterations += 1

        #save computed centroids
        self.centroids = centroids
        return self
    
    def fit_transform(self, X: np.matrix):
        self.fit(X)
        return self._compute_clusters(X, self.centroids)


if __name__  == "__main__":
    #fake dataset 
    np.random.seed(42)
    n_samples = 100
    cluster1 = np.random.normal(loc=2.0, scale=0.5, size=(n_samples, 2))
    cluster2 = np.random.normal(loc=7.0, scale=0.6, size=(n_samples, 2))
    x = np.vstack((cluster1, cluster2))
    y = np.array([0] * n_samples + [1] * n_samples)
    
    kmeans = Cluster(n_clusters=2, max_iter=200)
    clusters = kmeans.fit_transform(x)

    #plot
    # plt.scatter(x[:, 0], x[:, 1], c=y, cmap='bwr', edgecolor='k')
    plt.scatter(x[:, 0], x[:, 1], c=clusters, cmap='bwr', edgecolor='k')
    plt.xlabel("Feature 0")
    plt.ylabel("Feature 1")
    plt.legend()
    plt.show()