def modular_exponentiation(a: int, b: int, M: int):
    """
    Given 3 number a, b, M, the modular exponentiation is:
    a^b % M
    The most efficient way to compute modular exponentiation is to leverage binary exponentiation, which reduces the exponent in half at every step 
    which has a time complexity of O(logn)
    """
    result = 1

    #loop untill the exponent is more than 0
    while b >= 1:

        if b & 1 == 1: #if the exponent is odd
            result = (result * a) % M
            b -= 1 #make the exponent even 

        else: #if the exponent is even the following properties is valid: a^b = (a^2)^(b/2)
            a = (a * a) % M #square the base
            b = b // 2 #halve the exponent

    return result
