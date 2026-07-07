from collections import defaultdict

current_link_state = defaultdict(
    dict,
    {
        "A": {"B": 5} 
    }
)


def compute_link_state(node, link_state: dict):
    for source_node in  link_state.keys():
        for destination_node in link_state[source_node]:
            cost = link_state[source_node][destination_node]

            if destination_node not in current_link_state[source_node] or current_link_state[source_node][destination_node] != cost:
                current_link_state[source_node][destination_node] = cost


    return current_link_state


if __name__ == "__main__":
    node = "C"
    link_state = {
        "C": {
            "A": 1,
            "B": 2,
            "D": 6,
            "E": 6
        }
    }

    print(compute_link_state(node, link_state))