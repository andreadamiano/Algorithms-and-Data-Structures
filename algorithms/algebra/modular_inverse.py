from  extended_euclidean import extended_euclidean

def modular_inverse(a: int, m: int):
    """
    A modular inverse of an integer a is an integer x such that:
    a*x=1 % m
    modular inverse does not always exists. The modular inverse exists only and only if a and m are relative prime (i.e. gcd(a,m) = 1)
    The modular inverse can be found by solving the following equation:
    a*x + m*y = 1
    where this equation can be solved using the extended Euclidean algorithm, 
    if we take the modulo of the expression above for both terms we get the modular inverse:
    a*x = 1 % m
    since y*m % m = 0
    so x will be the modular inverse 
    """
    gcd, x, _ = extended_euclidean(a, m)
    
    if gcd != 1:
        raise Exception("No modular inverse found")

    #x is the modular inverse, but in order to make it a positive value we have to take into accoutn how programming languages handles modulo with negative numbers 
    #e.g -7 % 5 gives -2 not 3 
    #this is beacuase in mathematics the remainder is always a positive quantity 
    #t overcome this we must add m after performing the modulo to get a positive number and take the modulo once again
    #python handles mathematical modulo instead, this formula is kept noehteless for educational purpose 
    x = ((x % m) + m) % m
    return x


if __name__ == "__main__":
    a = 3
    m = 11
    print(modular_inverse(a,m))