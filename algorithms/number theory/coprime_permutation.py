from collections import defaultdict

MOD = 10**9 + 7

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


def compute_factorials(max_num: int ):
    """
    Bottom up iterative DP approach
    """
    factorials = [1] * (max_num + 1)

    for i in range(2, max_num + 1):
        factorials[i] = (factorials[i-1] * i) % MOD

    return factorials


def comprime_permutation(n: int, numbers: list[int]):
    #the first step is to compute the core (the unique prime numbers whose product generate the number) of every number using the siege of Eratosthenes
    #the sieve of Eratosthenes consists in computing the smallest prime number for every number, to compute the core, simply recurse over the smallest prime number computed as a cached array 
    spn = [1] * (n+1)

    for i in range(2, n+1):
        if spn[i] != 1:
            continue

        current = i
        while current < n+1:
            if spn[current] == 1: #only set the smallest prime factor, many numbers can have multiple prime factors save just the smallest (which is the first we encounter)
                spn[current] = i
            current += i


    core_buckets = defaultdict(int)
    cores = {}

    for i in range(1, n+1):
        core = 1
        current = i
        primes = set()
        while current != 1:
            prime = spn[current]

            if prime not in primes:
                core *= prime
                primes.add(prime)

            current //= prime

        cores[i] = core
        core_buckets[core] += 1

    #the problem states that every element mmust respect the followig property gcd(i, j) = 1 if gcd(p_i, p_j) = 1
    #in reverse this means that if two indices share a prime factor (gcd != 1), if we decided to permute them their new positions (p_i and p_j) MUST ALSO share that prime factor
    #therefore indices in the same core group can only be mapped to indicices of the same group.
    #the mapping on each group is a bijection: every index maps to a unique index inside the same group, using every position up with no duplicates.
    #the permutation of all valid numbers is just the mulitplications of the permutation of each group, since they are indipendent from each others
    #for instane a group of 2 items has 2! possible permutations
    #count the number of large primes (which are greater than n/2), this number can be merged with the bucket of numbers sharing a core of 1, since they share the same propery, which is they are coprime to all other numbers of the array
    for i in range(n//2+1, n+1):
        if core_buckets[i] == 1 and spn[i] == cores[i]: #check if the nunmmber is prime and if its bucket size is 1, that way we are sure it share the same prime factor with 1
            core_buckets.pop(i)
            core_buckets[1] += 1
            cores[i] = 1 #even if its not actually 1, we assign a value of 1 sine they share the same prime-factor DNA (meaning they are coprime to every other number in the list)

    #take into account fixed values
    #if a fixed value is in the right index bucket we decrement the bucket size, since the possible permmutation will be (n-1)!
    #if a fixed value is at the wrong index bucket no valid permutations are possible 

    for index, num in enumerate(numbers):
        if num:
            if cores[index+1] == cores[num]:
                core_buckets[cores[num]] -= 1

            else:
                return 0


    #precompute factorials
    factorials = compute_factorials(n)

    #compute the number of possiblle permutations by multiplying the permutations of every single bucket
    result = 1
    for bucket_size in core_buckets.values():
        if bucket_size:
            result *= factorials[bucket_size]

    return result % MOD

    

    

if __name__ == "__main__":
    # n = int(input())
    # numbers: list = [int(x) for x in input().split()]

    n = 4
    numbers = [0, 0, 0, 0]

    # n = 5
    # numbers = [0, 0,1, 2, 0]

    # n = 7
    # numbers = [0, 0, 0, 0, 0, 0, 0]

    n = 1000000
    numbers = [0] * n
    print(comprime_permutation(n, numbers))