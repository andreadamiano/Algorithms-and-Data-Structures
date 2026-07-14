from collections import defaultdict

current_distance_vector = defaultdict(
    lambda: [float("inf"), None],
    {
        "A": [0, "A"],
        "C" : [1, "C"]
    }
) 
#we track the gateway node for each destination. 
#if our current gateway reports a metric change (even a worse cost or infinity), 
#we must overwrite our table immediately because our path is dependent on their state.



def update_distance_vector(neighbor_node: str, distance_vector: dict):
    """
    Router sends:
        - periodic updates of their current distance vector
        - flash alerts when they detect changes in a local link
    """
    if neighbor_node not in current_distance_vector:   #we can't perform relaxation if we dont have the node stored in the distance vector (the node has to discover the new neighbor first in order to get the cost of the direct edge)
        return  

    for destination in distance_vector.keys():
        cost = current_distance_vector[neighbor_node][0] + distance_vector[destination][0]

        if destination == neighbor_node or destination == "A": #ignore direct edge or self loop 
            continue

        elif current_distance_vector[destination][1] == neighbor_node: #if an update arrives from the current gateway we must accept it
            current_distance_vector[destination] = [cost, neighbor_node]

        elif distance_vector[destination][1] == "A":
            continue #never accept a route that involves the current node as a gateway (to avoid the split horizon issue)

        elif current_distance_vector[destination][0] > cost: #perform relaxation (brute force distrubuted approach)
            current_distance_vector[destination] = [cost, neighbor_node]

    return current_distance_vector
    


if __name__ == "__main__":
    node = "C"
    distance_vector = {
        "C" : [0, "C"],
        "A" : [1, "A"],
        "B" : [2, "B"],
        "D" : [6, "D"],
        "E" : [6, "E"],
    } #vector distance mapping the distance from node c to every other node 
    print(update_distance_vector(node, distance_vector))

    distance_vector = {
        "C" : [0, "C"],
        "A" : [1, "A"],
        "B" : [float("inf"), "B"],
        "D" : [6, "D"],
        "E" : [6, "E"],
    }
    print(update_distance_vector(node, distance_vector))