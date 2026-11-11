def find_moves(machines: list): 
    total, n = sum(machines), len(machines)
    if total % n:
        return -1
    swaps = prefix = 0
    target = sum(machines)/len(machines)
    for machine in machines:
        diff = machine - target
        prefix += diff
        swaps = max(swaps, max(diff, abs(prefix)))  #the bottleneck is the max between the flow a node has to move in one direction to satisfy other machines' requiremetns and the number of clothes the machines has to move to reach its requirement

    return swaps


if __name__ == "__main__":
    machines = [1, 0, 5]
    print(find_moves(machines))