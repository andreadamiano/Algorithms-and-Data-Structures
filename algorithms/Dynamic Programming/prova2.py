def combination(N, k):
    """
    combination N choose k
    """
    subsets = []
    combinations(0, 0, N, k, subsets)
    return subsets

def combinations(set, at, N, k, subsets):
    if k ==0:
        subsets.append(set)

    for i in range(at, N):
        set |= (1 << i)
        combinations(set, i+1, N, k-1, subsets)
        #backtracking
        set ^= (1 << i)