from collections import defaultdict

current_distance_vector = defaultdict(
    lambda: float("inf"),
    {
        "A": 0,
        "C" : 1
    }
)



def update_distance_vector(neighbor_node: str, distance_vector: dict):
    if neighbor_node not in current_distance_vector:   #we can't perform relaxation if we dont have the node stored in the distance vector (the node has to discover the new neighbor first in order to get the cost of the direct edge)
        return  

    #perform relaxation (brute force distrubuted approach)
    for destination in distance_vector.keys():
        current_distance_vector[destination] = min(current_distance_vector[destination], current_distance_vector[neighbor_node] + distance_vector[destination])

    return current_distance_vector
    


if __name__ == "__main__":
    node = "C"
    distance_vector = {
        "C" : 0,
        "B" : 2,
        "D" : 6,
        "E" : 6,
    } #vector distance mapping the distance from node c to every other node 
    print(update_distance_vector(node, distance_vector))