def extended_euclidean(a: int, b: int):
    """
    While the euclidean algorithm allow to compute the greatest common divider:
        - by iteratively dividing the greatest number of the pair
        - finding the rest
        - swapping the smallest number with the biggets and the rest of the division with the smallest number
        - iterate untill the rest is null.

    The extended version also find a way to represent the gcd as a linear combination of the 2 numbers such that:
    a*x + b*y = gcd(a,b)
    to compute the coefficient recursively as we go down the Euclidean algorithm, remember the identity:
    gcd(a,b)=gcd(b,a%b) -> gcd = ax + by = bx1 + (a % b)y1
    (a%b) can also be rewritten as a-floor(a/b)*b
    using this identity we can express the gcd as a linear combination of:
    g = bx1 + (a - floor(a/b)*b)*y1
    which can be rewritten as:
    a*y1 + b*(x1-y1*floor(a/b))
    therefore from the previous relation:
    ax + by = bx1 + (a % b)y1
    we get that:
    x = y1
    y = (x1 - y1*floor(a/b))
    this define a relation between the current coefficeints and the next coefficients.
    This relationship has only one defect, specifies the current coefficient as a function of the next coefficient, so in order to compute them we must first recurse down the algorithm and
    then bubble up.
    To find them iteratively instead we must express each of the 2 current number A and B obtained iterating over the euclidean algorithm,
    as a linear combination of the original number a and b. As we progress down the Euclidan algorithm the next numbers of the sequence are equal to:
    B' = A - qB
    A' = B
    we use the previous linear combinations to express the newly found number as a linear combination of the previous number a and b:
    A' = B = xb*a + yb*b
    B' = A - q*B = (xa*a + ya*b) - q*(xb*a + yb*b) = (xa - q*xb)*a + (ya - q*yb)b
    which as a result provides:
    xa' = xb
    ya' = yb
    xb' = xa - q*xb
    yb' = ya - q*yb
    This relation express the next coefficient as a linear combination of the old coeffients, which is exactly what we need for the iterative solution.
    At every iteration, since the linear combiation should be equals at every steps, the coefficient shoould be equal, therefore the equation obtained.
    """

    xa, ya = 1, 0
    xb, yb = 0, 1

    while b:
        #no need to find the biggest number since the smallest will be swapped with the bigger at the first iteration
        q = a // b

        a, b = b, a - q * b
        xa, ya, xb, yb = xb, yb, xa - q * xb, ya - q * yb

    return a, xa, ya


if __name__ == "__main__":
    a = 270
    b = 192
    print(extended_euclidean(a, b))

