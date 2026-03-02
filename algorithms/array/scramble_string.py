memo = {}

def scramble_string(s1: str, s2: str):
    if s1 == s2: 
        return True
    
    key = f"{s1}#{s2}"
    if key in memo:
        return memo[key]
    
    #prune before recursing (avoid redundand check)
    if sorted(s1) != sorted(s2):
        memo[key] = False
        return False
    
    n = len(s1)
    for i in range(1, n):
        # No swap
        if scramble_string(s1[:i], s2[:i]) and scramble_string(s1[i:], s2[i:]):
            memo[key] = True
            return True
        # Swap
        if scramble_string(s1[:i], s2[n-i:]) and scramble_string(s1[i:], s2[:n-i]):
            memo[key] = True
            return True

    memo[key] = False
    return False



if __name__ == "__main__":
    s1 = "great"
    s2 = "rgeat"
    print(scramble_string(s1, s2))