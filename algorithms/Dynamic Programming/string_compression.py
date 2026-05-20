def min_lenght(s: str, k: int):
    memo = {}    
    def count(i, k, prev, prev_count):
        if (i, k, prev, prev_count) in memo:
            return memo[(i, k, prev, prev_count)]
        if k < 0:
            return float("inf")

        if i == len(s):
            return 0

        if s[i] == prev: #if the previous character is equal to the current it makes no sense to eliminate it, since it would be compressed anyway
            increment = 0
            if prev_count in [0, 1, 9, 99]:
                increment += 1 

            result = increment + count(i+1, k, prev, prev_count+1) 
        
        else: #if the previous and the current char are not identical find the better solution between deleting or not
            result = min(
                1+ count(i+1, k, s[i], 1),
                count(i+1, k-1, prev, prev_count)
                )
            
        memo[(i, k, prev, prev_count)] = result
        print(f"i={i}, k={k}, prev='{prev}', prev_count={prev_count} → {result}")
        return result

    return count(0, k, "", 0)


if __name__ == "__main__":
    # s = "aaabcccd"
    s = "aaaaaaaaaabbb"
    # k = 2
    k = 1
    print(min_lenght(s, k))