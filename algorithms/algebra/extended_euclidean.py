def extended_euclidean(a: int, b: int):
    """
    While the euclidean algorithm allow to compute the greatest common divider by iteratively dividing the greatest numberof the pair, finding the rest 
    swapping the smalles with the biggets and the rest with the smallest untill the rest is null. The extended version also find a linear combination of the 2 numbers such that:
    a*x + b*y = gcd(a,b)
    to compute the coefficient recursively as we go down the Euclidean algorithm, remember the identity:
    gcd(a,b)=gcd(b,a%b) -> gcd = ax + by = bx1 + (a % b)y1
    (a%b) can also be rewritten as a-floor(a/b)*b, the idea behind is simple, find the max number of times a can be divided by b without overflowing and then find the rest 
    using this identity we can express the gcd as a linear combination of:
    g = bx1 + (a - floor(a/b)*b)*b = a*y1 + b*(x1-y1*floor(a/b))
    therefore if we resume the relation gcd(a,b)=gcd(b,a%b) we get that 
    x = y1
    y = (x1 - y1*floor(a/b))
    this define a relation between the current coefficeints and the next coefficients as we perform the Euclidean algorithm.
    This relationship has only one defect, specifies the current coefficient as a function of the next coeffieint, so in order to compute them we must first recurse down the algorithm and 
    then bubble up to compute them
    To find them iteratively instead we must express each of the 2 starting numbers a and b as a linear combination of the original number a and b, then as we progress down the Euclidan algorithm 
    computing the next number of the sequence B'= A - qB, we use the previous linear combinations to express the newly found number as a linear combination of the original number a and b iteratively adjusting the coefficients:
    xa' = xb
    ya' = yb
    xb' = xa - q*xb
    yb' = ya - q*yb
    this is the result of:
    A' = B = xb*a + yb*b      
    B' = A - q*B = (xa*a + ya*b) - q*(xb*a + yb*b) = (xa - q*xb)*a + (ya - q*yb)b
    , where A and B represent the current A and B computed by the algorithm and a and b the origal input numbers.
    This relation express the next number in the algotihm as a linear combination of the old coeffients (modified) and the original numbers, which is exactly what we need for the iterative solution.
    At every iteration, since the linear combiation should be equals at every steps, also the coefficient shoould be equal, therefore the equation.
    """

    if a != max(a,b): #make sure a is the bigger
        a, b = b, a

    xa, ya = 1, 0 
    xb, yb = 0, 1
   
    while b:
        q = a // b

        a, b = b, a - q*b
        xa, ya, xb, yb = xb, yb, xa - q * xb, ya - q * yb

    return xa, ya


if __name__ == "__main__":
    a=270
    b=192
    print(extended_euclidean(a,b))