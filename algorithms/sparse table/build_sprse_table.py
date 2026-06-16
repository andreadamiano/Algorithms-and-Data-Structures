import math

def build_sparse_table(array: list):
    """
    The sparse table stores at each cell the min element in the range of lenght 2^i
    """
    n = len(array)
    log_n = int(math.log2(n)) + 1  #+1 to store also the base case inside the dp table
    sparse_table = [[0] * n for _ in range(log_n)] #d[j][i] store the min element in the range j:2^i
    sparse_table[0] = array[:]

    for j in range(1, log_n):
        for i in range(n - (1 << j) + 1):
            sparse_table[j][i] = min(sparse_table[j-1][i], sparse_table[j-1][i + (1 << (j-1))]) #look at the min of the 2 halves 

    for row in sparse_table:
        print(row)

    return sparse_table


def find_min(array: list, left: int, right: int):
    """
    The idea is that we want to find the range of lenght (right - left + 1)
    Since we have already precomputed the min values for a range 2^k, we use the largest power of 2 that is <= (right - left + 1)
    The solution leverage the properties that min operation is idempotent (meaning that the result is the same no matter the order of operations)
    So we find the min between 2 overlapping ranges, since we are not sure that there is a power of 2 exatly equals to the range (right - left + 1)
    """
    sparse_table = build_sparse_table(array)
    k = int(math.log2(right - left +1))
    return min(sparse_table[k][left], sparse_table[k][right - (1 << k) + 1]) #find the min between 2 intervals (left to k) (right - 2^k +1 to k) so we are sure to cover the entire range

if __name__ == "__main__":
    array = [2, 5, 3, 6, 4, 1, 9, 7]
    print(find_min(array, 2, 5))