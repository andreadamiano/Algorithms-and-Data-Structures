from collections import defaultdict

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
    #the first step is to compute the core (the unique prime numbers whose product generate the number) of every number using the siege of Eratosthenes
    #the sieve of Eratosthenes consists in computing the smallest prime number for every number, to compute the core, simply recurse over the smallest prime number computed as a cached array 
    spn = [1] * (n+1)

    for i in range(2, n+1):
        if spn[i] != 1:
            continue

        current = i
        while current < n+1:
            spn[current] = i
            current += i


    core_buckets = defaultdict(int)

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

        core_buckets[core] += 1

    #count the number of large primes (which are greater than n/2), this number can be merged with the bucket of numbers sharing a core of 1, since they share the same propery, which is they are coprime to all other numbers of the array
    
    #the problem states that every element mmust respect the followig property gcd(i, j) = 1 if gcd(p_i, p_j) = 1
    #in reverse this means that if two indices share a prime factor (gcd != 1), if we decided to permute them their new positions (p_i and p_j) MUST ALSO share that prime factor
    #therefore numbers in the same core group can only be mapped to elements of the same group
    #the permutation of all valid numbers is just the mulitplications of the permutation of each group, since they are indipendent frm each others
    #for instane a group of 2 items has 2! possible permutations
    for i in range(n//2+1, n+1):
        if core_buckets[i] == 1:
            core_buckets.pop(i)
            core_buckets[1] += 1

    return core_buckets

    

    

if __name__ == "__main__":
    # n = input()
    # numbers: list = [int(x) for x in input().split()]

    n = 4
    numbers = [0, 0, 0, 0]
    print(comprime_permutation(n, numbers))