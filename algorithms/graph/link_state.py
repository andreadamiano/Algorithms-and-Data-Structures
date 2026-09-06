from collections import defaultdict

current_link_state = defaultdict(
    dict,
    {
        "A": {"B": 5},
        "C":{"F":2}
    }
)

def compute_link_state(node, link_state: dict):
    """
    Routers sends:
        - periodic LSP packet where they essentially communincate ONLY their adjency list 
        - flood the others LSP packets so that the entire network will listen to it 

    As a result every node will store the full adjency list of the entire graph
    """

    remaining_nodes = set(current_link_state[node])

    for destination_node, cost in link_state.items():

        if destination_node in remaining_nodes:
            remaining_nodes.remove(destination_node)

        if destination_node not in current_link_state[node] or current_link_state[node][destination_node] != cost:
            current_link_state[node][destination_node] = cost

    for remaining_node in remaining_nodes: #if a node stop reporting an edge it means that edge is probably dead, therefore remove it from the global state
        current_link_state[node].pop(remaining_node)


    return current_link_state


if __name__ == "__main__":
    node = "C"
    link_state = {
        "A": 1,
        "B": 2,
        "D": 6,
        "E": 6
    }

    print(compute_link_state(node, link_state))