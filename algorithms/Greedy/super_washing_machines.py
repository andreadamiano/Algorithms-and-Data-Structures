def find_moves(machines: list): 
    total, n = sum(machines), len(machines)
    if total % n:
        return -1
    swaps = prefix = 0
    target = sum(machines)/len(machines)
    for machine in machines:
        diff = machine - target
        prefix += diff
        swaps = max(swaps, max(diff, abs(prefix)))

    return swaps


if __name__ == "__main__":
    machines = [1, 0, 5]
    print(find_moves(machines))