import heapq

def move_candies(n: int, candies: list):

    def count(heap: list):
        boxes = 0

        for candy, _ in heap:
            if candy:
                boxes += 1

        return boxes

    heap = []
    n_moves = 0
    moves = []
    a = b = c = 0

    for index, candy in enumerate(candies):
        if candy:
            heapq.heappush(heap, (candy, index))

    boxes = count(heap)

    if boxes < 2:
        return -1, []
    
    while  boxes > 2:

        a, a_index = heapq.heappop(heap)
        b, b_index = heapq.heappop(heap) #accumulator
        c, c_index = heapq.heappop(heap) #drain

        quotient = b // a

        while quotient:  
            #use binary notation to accumulate the division on operand b, while multiplying at every step
            #binary notation allow to subctract a to b only when it's needed (meaning only when the right power of 2 compose the quotient number)
            #this simulate the same way ALU does division, by repeatedly shifting (to obtain the largest possible power of 2 that is less the the numerator) and subsctracting it from the accumualtor
            #if the current bit is 0 it mean that the current power of 2 must not be subtracted to b, for this reason c acts as a sink satisfying the request from a to be doubled
            if quotient & 1: 
                b -= a
                moves.append((a_index+1, b_index+1))

            else:
                c -= a    
                moves.append((a_index+1, c_index+1))

            a = a << 1 #double a at every iteration
            quotient = quotient >> 1 #consume every bit of the quotient
            n_moves += 1

        if a:
            heapq.heappush(heap, (a, a_index))

        if b:
            heapq.heappush(heap, (b, b_index))

        if c:
            heapq.heappush(heap, (c, c_index))

        boxes = count(heap)

    return n_moves, moves

if __name__ == "__main__":
    # n = 3
    # candies = [3, 6, 9]

    # n = 3
    # candies = [0, 1, 0]

    # n = 4
    # candies = [0, 1, 1, 0]

    # n = 3
    # candies = [3, 7, 8]

    # n = 10
    # candies = [3, 6, 5, 5, 4, 5, 5, 4, 7, 6]

    # n = 50
    # candies = [3, 1, 2, 5, 3, 3, 2, 3, 0, 1, 2, 4, 1, 1, 2, 1, 0, 1, 3, 2, 2, 3, 2, 4, 3, 1, 2, 0, 4, 2, 2, 3, 1, 2, 2, 1, 2, 2, 3, 3, 0, 0, 1, 1, 2, 4, 1, 3, 2, 2]

    n = input()
    candies = input() #convert into a list
    candies = [int(candy) for candy in candies.split()]

    n_moves, moves = move_candies(n, candies)
    print(n_moves)
    for move in moves:
        print(f"{move[0]} {move[1]}")