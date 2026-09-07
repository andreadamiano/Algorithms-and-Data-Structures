def coprime(num1, num2):
    """
    Compute if 2 numbers are comprime by checking if their GCD is 1
    the GDC is computed using the Euler algorithm
    """
    bigger, smaller = num1, num2
    if bigger != max(num1, num2):
        smaller, bigger = bigger, smaller

    while True: 
        rest = bigger % smaller

        if not rest:
            break

        bigger, smaller = smaller, rest

    return True if smaller == 1 else False




def comprime_permutation(n: int, numbers: list[int]):

    def create_permutations(number_set: set, position: int = 0, current_permutation: list = [0] * n):
        """
        In order for a permmutation to be valid, for every coprime indices the corresponding elements must also be coprime and viceversa
        """
        if not number_set:
            return 1

        valid_permutations = 0
        for number in number_set.copy(): #iterate over a copy to avoid the undefined behavior of iterating over a changing set 

            current_permutation[position] = number

            if not position or coprime(current_permutation[position], current_permutation[position-1]):
                number_set.remove(number)
                valid_permutations += create_permutations(number_set, position+1, current_permutation)
                number_set.add(number)

        return valid_permutations


         

    #preprocessing, remove all already used numbers from the set of availbale nummbers before computing all possible permutations
    number_set = set([x for x in range(1, n+1)])
    for number in numbers:
        if number: 
            number_set.pop(number)

    valid_permutations = create_permutations(number_set)
    return valid_permutations
    

    

if __name__ == "__main__":
    # n = input()
    # numbers: list = [int(x) for x in input().split()]

    n = 4
    numbers = [0, 0, 0, 0]
    print(comprime_permutation(n, numbers))