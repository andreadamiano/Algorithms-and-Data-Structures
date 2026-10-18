from algorithms.algebra.modular_inverse import modular_inverse
from collections import defaultdict

MOD = 10**9 + 7  # prime

# in competitive programming never compute floating point division, always use the modular inverse instead
# for variable exponentiation operation, always compute modular exponentiation
# for multiplication, addition and subtractions always take the modulo instead
INV2 = modular_inverse(2, MOD)
INV4 = modular_inverse(4, MOD)
INV8 = modular_inverse(8, MOD)
INV16 = modular_inverse(16, MOD)

cache = {}
stack = []


def find_cycles(
    adj_dict: dict[list[int]],
    cycle_list: list,
    visited=None,
    current_node=1,
    parent_node=None,
    timer=1,
):  # if no parent is specified we root the spanning tree at node 1
    """
    This is a modifed block decomposition algorithm, since cactus graph every edge belongs to at most one simple cycle. A cycle is guaranteed to be a block with edges >= 3.
    """

    if not visited:
        visited = set()

    encountered = lower = timer
    cache[current_node] = (encountered, lower)
    visited.add(current_node)

    for neighbor in adj_dict[current_node]:
        if neighbor == parent_node:  # do not visit the parent
            continue

        if (neighbor in visited and parent_node):  # if the node was already visited, it means there is a cycle, which means that the current node has a shortcut to a node that is higher on the spanning tree
            child_encountered, child_lower = cache[neighbor]
            lower = min(child_encountered, lower)
            stack.append((current_node, neighbor))  # append the visited edge on the FIFO stack to pop them when a bottleneck node is found

        elif neighbor not in visited:
            stack.append((current_node, neighbor))  # append the visited edge on the FIFO stack to pop them when a bottleneck node is found
            _, (child_encountered, child_lower) = find_cycles(adj_dict, cycle_list, visited, neighbor, current_node, timer + 1)
            lower = min(child_lower, lower)

            # check if the current node is a bottleneck node for the current child
            if (child_lower >= encountered):  # if the node didn't find any higher level nodes to hold on to, it means that the parent is the bottleneck node
                vertices_set = set()
                while True:
                    edge = stack.pop()
                    vertices_set.add(edge[0])
                    vertices_set.add(edge[1])

                    if edge == (current_node, neighbor):
                        break

                if (len(vertices_set) > 2):  # if a block has more then 3 or more vertices is must be a cycle
                    cycle_list.append(vertices_set)

    cache[current_node] = (encountered, lower)  # cache the new lower found
    return cycle_list, cache[current_node]


def remove_cactus(n, m, edges):
    """
    Cactus graphs are connected graphs where any 2 simple cycles shares at most one vertex
    """
    adj_dict = defaultdict(list)
    degs = defaultdict(int)

    for source, dest in edges:
        adj_dict[source].append(dest)
        adj_dict[dest].append(source)
        degs[source] += 1
        degs[dest] += 1

    # Euler formula: V - E + F = 2 , which mweans that adding an edge should either create a new vertex or a new face
    # modified Euler formula: V - E + cycles = connected components
    cycles = []
    cycles, _ = find_cycles(adj_dict, cycles)

    # from the linearity of expectations: E[connected components] = E[V] - E[E] + E[cycles]
    e_e = ((INV4) * m) % MOD  # sum of probabilities that an edge remains
    e_v = ((INV2) * n) % MOD  # sum of probabilities that a vertex remain
    e_cycle = (sum(pow(INV2, len(cycle), MOD) for cycle in cycles) % MOD)  # sum of probabilities that a cycle remain
    e_components = (e_v - e_e + e_cycle) % MOD

    # variance = E[x^2] - E[x]^2
    # since we already know that E[x] = E[V] - E[E] + E[cycles]
    # expanding the square of a trinome we get: x^2 = V^2 + E^2 + cycles^2 - 2V*E + 2V*cycles - 2E*cycles
    # from the llnearity of expectations: E[X^2] = E[V^2] + E[E^2] + E[cycles^2] - 2E[V*E] + 2E[V*cycles] -2E[E*cycles]
    # to find the expectation of a squared random variable X^2 recall that
    # X=x1+x2+x3+... , where xi represent bernoulli indicator random variable, which is a simple switch indicating if the event occur or not (0 or 1)
    # X^2 = (x1+x2+...) * (x1+x2+...)=x1x1 + x1x2 + ... + x2x2
    # therefore by linearity of expectations we get: E[X^2] = sum_{i} sum_{j} E[xi * xj]
    # for the elements on the diagonal: p(x1x1)=p(x1) since 1^2 and 0^2 is identical to p(x1)
    # for the off-diagonal terms: p(x1x2))=p(x1)p(x2) if the 2 events are indipendent
    # therefore the general formula becomes: E[X^2]=n*p + (n^2 - n)*p^2

    e_v_2 = ( ((INV2) * n + (n**2 - n) * (INV4)) % MOD)  # the off-diaginal elements represent the probability of 2 disjoint vertices

    # the off-diagonal elements fall into 2 categories:
    # the edges that share 1 vertex
    # the edges that shares 0 vertex
    # to find all the pair of edges sharing 1 vertex compute sum_{i} deg(i)(deg(i)-1) (we count every pair twice since xixj element of the matrix is the same as xjxi)
    a = sum(deg * (deg - 1) for deg in degs.values())
    e_e_2 = ((INV4) * m + a * (INV8) + (m**2 - m - a) * (INV16)) % MOD

    # in the case of cycle-cycle pair the expectation of the off-diagonal c1 and c2 depends on the number of vertex they share
    e_c_2 = 0
    for i, cycle1 in enumerate(cycles):
        for j, cycle2 in enumerate(cycles):
            if i == j: #they are the same cycle 
                e_c_2 = (e_c_2 + pow(INV2, len(cycle1), MOD)) % MOD

            else: 
                shared_vertices = len(cycle1.intersection(cycle2)) #compute how many edges they share to get the probability of both cycles to remain
                n_disjoint_vertices = len(cycle1) + len(cycle2) - shared_vertices
                e_c_2 = (e_c_2 + pow(INV2, n_disjoint_vertices, MOD)) % MOD

    e_v_e = (((INV4) * 2 * m + (n * m - 2 * m) * (INV8)) % MOD)  #the off-diagonal elements represents the probability of having a vertex which is not part of the considered edge

    e_v_c = 0
    for cycle in cycles:
        cycle_len = len(cycle)
        e_v_c = ((e_v_c + cycle_len * pow(INV2, len(cycle), MOD) + (n - cycle_len) * pow(INV2, cycle_len + 1, MOD)) % MOD )  # p represent the probability of having a vertex part of the current cycle

    # the off-diaginal elements fall into 2 categories:
    # the edges that share 1 vertex with the cycle and the edges that are completely disjoint
    e_e_c = 0
    for cycle in cycles:
        cycle_edges = len(cycle)
        incident_edges = sum(degs[vertex] - 2 for vertex in cycle)  # -2 since 2 edges are already part of the cycle
        disjoint_edges = m - cycle_edges - incident_edges
        e_e_c = (e_e_c + cycle_edges * pow(INV2, cycle_edges, MOD) + incident_edges * pow(INV2, cycle_edges + 1, MOD) + disjoint_edges * pow(INV2, cycle_edges + 2, MOD)) % MOD

    e_components_2 = (e_v_2 + e_e_2 + e_c_2 + 2 * e_v_c - 2 * e_v_e - 2 * e_e_c) % MOD
    variance = (e_components_2 - e_components**2) % MOD
    return variance


if __name__ == "__main__":
    n = 3  # nodes
    m = 3  # vertices
    edges = [[1, 2], [2, 3], [1, 3]]
    print(remove_cactus(n, m, edges))

